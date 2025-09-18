#include "AllInput.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "FileOperations.h"

PossibleErrors parse_argv(int argc, char *argv[], TypesOfSort *sorting_type, const char **filename_in, const char **filename_out) {
    assert(argv         != NULL);
    assert(sorting_type != nullptr);

    size_t pos = 1;
    PossibleErrors err = kNoError;

    if (argc > 1) {
        err = parse_arguments(argc, argv, pos, filename_in, filename_out, sorting_type);
        if (err != kNoError) {
            return err;
        }
        
    }

    return kNoError;
}

char *read_to_buf(const char *filename, FILE *file, size_t filesize) {
    assert(filename != NULL);
    assert(file     != NULL);

    char *buf_in = (char *) calloc(filesize + 2, sizeof(char));
    assert(buf_in != NULL);

    size_t bytes_read = fread(buf_in, sizeof(buf_in[0]), filesize, file);
    if (bytes_read == 0) {
        buf_in[0] = '\n';
        buf_in[1] = '\0';

    } else {
        if (buf_in[bytes_read - 1] != '\n') {
            buf_in[bytes_read] = '\n';
            bytes_read++;
        }

        buf_in[bytes_read] = '\0';
    }

    return buf_in;
}

size_t parse_buf(char *buf, struct LineInfo *text_ptr, size_t bufsize) {
    assert(buf      != NULL);
    assert(text_ptr != NULL);

    size_t line_idx = 0;
    char *line_start = buf;
    char *alpha_start = NULL;
    char *alpha_end = NULL;

    bufsize++;
    for (size_t i = 0; i <= bufsize; i++) {
        char c = buf[i];
        int end_of_buffer = (i == bufsize);
        int end_of_line = (c == '\n' || end_of_buffer);

        if (!end_of_line) {
            if (isalpha((unsigned char)c)) {
                if (alpha_start == NULL) {
                    alpha_start = &buf[i];
                }

                alpha_end = &buf[i];
            }
        }

        if (end_of_line) {
            // if (line_idx >= LINECOUNT) {
            //     break;
            // }

            text_ptr[line_idx].start_ptr = line_start;
            text_ptr[line_idx].end_ptr = &buf[i - 1];

            text_ptr[line_idx].start_ptr_alpha = alpha_start;
            text_ptr[line_idx].end_ptr_alpha = alpha_end;

            text_ptr[line_idx].size = (size_t)(&buf[i - 1] - line_start) + 1;

            line_idx++;

            line_start = &buf[i + 1];
            alpha_start = NULL;
            alpha_end = NULL;
        }
    }
    line_idx--;

    return line_idx;
}

PossibleErrors buf_input(const char *filename, LineInfo **text_ptr, char **buf_ptr, size_t *line_count, size_t filesize) {
    assert(filename != NULL);

    FILE *file = open_file(filename, READ_MODE);
    if (file == NULL) {
        perror("fopen() failed");
        return kErrorOpening;
    }

    *buf_ptr = read_to_buf(filename, file, filesize);
    assert(buf_ptr != NULL);

    *line_count = count_lines(*buf_ptr);

    *text_ptr = (struct LineInfo *) calloc(*line_count + 1, sizeof(LineInfo));
    PossibleErrors err = handle_parse_buf(*text_ptr, *buf_ptr, filesize, file);

    return err;
}

PossibleErrors handle_parse_buf(struct LineInfo *text_ptr, char *buf_ptr, size_t filesize, FILE *file) {
    assert(text_ptr != NULL);

    parse_buf(buf_ptr, text_ptr, filesize);

    int err = close_file(file);
    if (err != kNoError) {
        perror("fclse() failed");
        return kErrorClosing;
    }

    return kNoError;
}

PossibleErrors parse_arguments(int argc, char *argv[], size_t pos, const char **filename_in, const char **filename_out, TypesOfSort *sorting_modes) {
    assert(argv         != NULL);
    assert(filename_in  != NULL);
    assert(filename_out != NULL);

    size_t i = pos;
    //size_t last_of_positions = pos + 6;

    while (i < (size_t)argc) {
        if (parse_in_out(argv, i, IN_MODE, filename_in)) {
            i += 2;

        } else {
            if (parse_in_out(argv, i, OUT_MODE, filename_out)) {
                i += 2;

            } else {
                if (parse_sorting_modes(argv, i, sorting_modes) == kNoError) {
                    i += 2;

                } else {
                    printf("Wrong mode %s.\n", argv[i]);
                    return kErrorParsing;
                }
            }
        }
    }

    return kNoError;
}

bool parse_in_out(char *argv[], size_t pos, const char *mode, const char **filename) {
    assert(argv     != NULL);
    assert(mode     != NULL);
    assert(filename != NULL);

    if (strcmp(argv[pos], mode) == 0) {
        *filename = argv[pos + 1];

        return true;
    }

    return false;

}

PossibleErrors parse_sorting_modes(char *argv[], size_t pos, TypesOfSort *sorting_modes) {
    assert(argv          != NULL);
    assert(sorting_modes != NULL);

    if (strcmp(argv[pos], SORT_MODE) == 0) {
        pos++;
        PossibleErrors err = check_sort_mode(argv[pos], sorting_modes);

        return err;

    } 
    
    return kNoSolution;
}
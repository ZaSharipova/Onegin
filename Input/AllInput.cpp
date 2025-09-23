#include "AllInput.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "FileOperations.h"

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

void parse_buf(FileInfo *file_info) {
    assert(file_info != NULL);

    size_t line_idx = 0;
    char *line_start = file_info->buf_ptr;
    char *alpha_start = NULL;
    char *alpha_end = NULL;
    size_t bufsize = file_info->filesize + 1;

    for (size_t i = 0; i <= bufsize; i++) {
        char c = file_info->buf_ptr[i];
        int end_of_buffer = (i == bufsize);
        int end_of_line = (c == '\n' || end_of_buffer);

        if (!end_of_line) {
            if (isalpha((unsigned char)c)) {
                if (alpha_start == NULL) {
                    alpha_start = &(file_info->buf_ptr[i]);
                }

                alpha_end = &(file_info->buf_ptr[i]);
            }
        }

        if (end_of_line) {
            long line_len = &(file_info->buf_ptr[i]) - line_start;
            if (!is_blank_line(line_start, (size_t)line_len) && alpha_start != NULL) {

                file_info->text_ptr[line_idx].start_ptr = line_start;
                file_info->text_ptr[line_idx].end_ptr = &(file_info->buf_ptr[i - 1]);

                file_info->text_ptr[line_idx].start_ptr_alpha = alpha_start;
                file_info->text_ptr[line_idx].end_ptr_alpha = alpha_end;

                file_info->text_ptr[line_idx].size = 
                (size_t)(&(file_info->buf_ptr[i - 1]) - line_start) + 1;

                line_idx++;
            }

            line_start = &(file_info->buf_ptr[i + 1]);
            alpha_start = NULL;
            alpha_end = NULL;
        }
    }
}

PossibleErrors handle_buf_read(const char *filename, FileInfo *file_info) {
    assert(filename  != NULL);
    assert(file_info != NULL);

    FILE *file = open_file(filename, READ_MODE);
    if (file == NULL) {
        perror("fopen() failed");
        return kErrorOpening;
    }

    file_info->filesize = (size_t)size_of_file(filename);

    file_info->buf_ptr = read_to_buf(filename, file, file_info->filesize);
    assert(file_info->buf_ptr != NULL);

    file_info->count_lines = (int)count_lines(file_info->buf_ptr);

    file_info->text_ptr = (struct LineInfo *) calloc ((size_t)file_info->count_lines + 1, sizeof(LineInfo));
    assert(file_info->text_ptr != NULL);

    parse_buf(file_info);

    return close_file(file);
}
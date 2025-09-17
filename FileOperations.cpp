#include "FileOperations.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#include "Sortings.h"
#include "AllOutputText.h"

int pointers_text(struct LineInfo *text_ptr) {
    assert(text_ptr != NULL);

    char *buf_ptr;
    size_t line_count = 0;
    buf_input("textonegin.txt", text_ptr, &buf_ptr, &line_count);

    //bubble_sort(text_ptr);
    quick_sort(text_ptr, 0, line_count, compare_LtoR);

    FILE *file = fopen("SortedOnegin.txt", "w");

    print_sorted_LtoR_label(file);
    output_with_buf(text_ptr, file);
    printf("Sorting  1 done. It is from line %zu\n", 4);

    //quick_sort(text_ptr, 0, line_count, compare_RtoL);
    //qsort(text_ptr, sizeof(char), size_of_file("textonegin.txt"), compare_RtoL);
    bubble_sort(text_ptr);

    print_sorted_RtoL_label(file);
    output_with_buf(text_ptr, file);
    printf("Sorting  2 done. You can see it from line %zu\n", FILESIZE + 7);

    print_original_label(file);
    output_original_text(file, buf_ptr);
    printf("Original Text is from line %zu\n", FILESIZE * 2 + 10);

    free(buf_ptr);
    return kNoError;
}

FILE *open_file(const char *filename, const char *mode) {
    assert(filename != NULL);
    assert(mode     != NULL);

    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        return NULL;
    }

    return file;
}

PossibleErrors close_file(FILE *file) {
    assert(file != NULL);
    assert(file != stdin);
    assert(file != stdout);

    int status = fclose(file);
    if (status != 0) {
        return kErrorClosing;
    }

    return kNoError;
}

long long size_of_file(const char *filename) {
    assert(filename != NULL);

    struct stat stbuf;

    int err = stat(filename, &stbuf);
    if (err != kNoError) {
        perror("stat failed");
        return -1; //добавить ключ
    }

    return stbuf.st_size;
}

char *read_to_buf(const char *filename, FILE *file) {
    assert(filename != NULL);
    assert(file     != NULL);

    size_t filesize = (size_t)size_of_file(filename);

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

size_t parse_buf(char *buf, struct LineInfo *text_ptr) {
    assert(buf      != NULL);
    assert(text_ptr != NULL);

    size_t line_idx = 0;
    char *line_start = buf;
    char *alpha_start = NULL;
    char *alpha_end = NULL;

    size_t bufsize = (size_t)size_of_file("textonegin.txt") + 1;
    //printf("%zu\n", bufsize);
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
            if (line_idx >= FILESIZE) {
                break;
            }

            text_ptr[line_idx].start_ptr = line_start;
            text_ptr[line_idx].end_ptr = &buf[i - 1];

            text_ptr[line_idx].start_ptr_alpha = alpha_start;
            text_ptr[line_idx].end_ptr_alpha = alpha_end;

            text_ptr[line_idx].size = &buf[i - 1] - line_start + 1;

            line_idx++;

            line_start = &buf[i + 1];
            alpha_start = NULL;
            alpha_end = NULL;
        }
    }
    return line_idx;
}

PossibleErrors buf_input(const char *filename, struct LineInfo *text_ptr, char **buf_ptr, size_t *line_count) {
    assert(filename != NULL);
    assert(text_ptr != NULL);

    FILE *file = open_file(filename, "r");
    if (file == NULL) {
        perror("fopen() failed");
        return kErrorOpening;
    }

    *buf_ptr = read_to_buf(filename, file);
    assert(buf_ptr != NULL);

    *line_count = parse_buf(*buf_ptr, text_ptr);

    //free(buf);

    int err = close_file(file);
    if (err != kNoError) {
        perror("fclse() failed");
        return kErrorClosing;
    }

    return kNoError;
}

void output_with_buf(struct LineInfo *text_ptr, FILE *file) {
    assert(text_ptr != NULL);
    assert(file     != NULL);

    size_t filesize = (size_t)size_of_file("textonegin.txt");
    char *buf_out = (char *) calloc(filesize + 5333, sizeof(char)); //размер подумать еще
    assert(buf_out != NULL);
    char *ptr = buf_out;

    for (size_t i = 0; i < FILESIZE; i++) { //

        memcpy(ptr, text_ptr[i].start_ptr, text_ptr[i].size);
        ptr += text_ptr[i].size;
        *ptr = '\n';
        ptr++;
    }
    *ptr = '\0';

    size_t size = strlen(buf_out);

    size_t status = fwrite(buf_out, sizeof(char), size, file);
    if (status != size) {
        perror("fwrite() failed");
    }

    //fclose(file);
    free(buf_out);
} 

void output_original_text(FILE *file, char *buf) {
    assert(file != NULL);

    size_t size = strlen(buf);

    fwrite(buf, sizeof(char), size, file);

    //free(buf);
    fclose(file);

}
//TODO добавить ассертов
//TODO tolower
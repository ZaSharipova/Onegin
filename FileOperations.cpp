#include "FileOperations.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#include "AllInput.h"
#include "AllOutput.h"

PossibleErrors handle_all_sort(FileInfo *file_info, ArgumentModes flags) {
    assert(file_info != NULL);

    FILE *file = open_file(flags.filename_out, WRITE_MODE);

    handle_switch_sort(file_info, flags.sort_mode, compare_ltor);
    output_all(file, file_info->text_ptr, CompareTypesDirect, (int)file_info->count_lines);

    handle_switch_sort(file_info, flags.sort_mode, compare_rtol);
    output_all(file, file_info->text_ptr, CompareTypesReverse, (int)file_info->count_lines);

    output_original(file, file_info->buf_ptr);
    
    PossibleErrors status = close_file(file);
    if (status != kNoError) {
        free(file_info->buf_ptr);
        return kErrorClosing;
    }

    free(file_info->buf_ptr);

    return kNoError;
}

void handle_switch_sort(FileInfo *file_info, TypesOfSort sort_mode, int (*compares)(const void *, const void *)) {
    assert(file_info != NULL);
    assert(compares  != NULL);

    switch (sort_mode) {
    case (TypesOfSortQsort):
        qsort(file_info->text_ptr, (size_t)file_info->count_lines, sizeof(LineInfo), compares);
        break;

    case (TypesOfSortBubble):
        bubble_sort(file_info->text_ptr, file_info->count_lines, compares);
        break;

    case (TypesOfSortMyQuick):
        quick_sort_with_stack(file_info->text_ptr, file_info->count_lines, 0, file_info->count_lines, compares);
        break;

    case (TypesOfSortInsertion):
        insertion_sort(file_info->text_ptr, 0, file_info->count_lines, compares);
        break;

    default:
        fprintf(stderr, "No such sorting type.\n");

    }
}

FILE *open_file(const char *filename, const char *mode) {
    assert(filename != NULL);
    assert(mode     != NULL);

    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("fopen() failed");
        return NULL;
    }

    return file;
}

PossibleErrors close_file(FILE *file) {
    assert(file != NULL);

    int status = fclose(file);
    if (status != 0) {
        perror("fclose() failed");
        return kErrorClosing;
    }

    return kNoError;
}

long long size_of_file(const char *filename) {
    assert(filename != NULL);

    struct stat stbuf;

    int err = stat(filename, &stbuf);
    if (err != kNoError) {
        perror("stat() failed");
        return kErrorStat;
    }

    return stbuf.st_size;
}

size_t count_lines(char *buf_ptr) {
    assert(buf_ptr != NULL);

    size_t counter = 0;
    char *line_start = buf_ptr;
    char *ptr = buf_ptr;

    while (*ptr != '\0') {
        if (*ptr == '\n') {
            size_t line_len = (size_t)(ptr - line_start);

            int has_alpha = 0;
            for (size_t i = 0; i < line_len; i++) {
                if (isalpha((unsigned char)line_start[i])) {
                    has_alpha = 1;
                    break;
                }
            }

            if (!is_blank_line(line_start, line_len) && has_alpha) {
                counter++;
            }

            line_start = ptr + 1;
        }
        ptr++;
    }

    return counter;
}

int is_blank_line(const char* start, size_t line_size) {
    for (size_t i = 0; i < line_size; i++) {
        if (!isspace((unsigned char)start[i]))
            return 0;
    }
    return 1;
}

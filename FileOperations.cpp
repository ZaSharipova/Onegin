#include "FileOperations.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#include "Sortings.h"
#include "AllOutputText.h"
#include "AllInput.h"
#include "AllOutput.h"

PossibleErrors check_sort_mode(char *str, TypesOfSort *type) {
    if (strcmp(str, "qsort") == 0) {
        *type = qsorting;

    } else {
        if (strcmp(str, "bubble_sort") == 0) {
            *type = bubble_sorting;

        } else {
            if (strcmp(str, "quick_sort") == 0) {
                *type = quick_sorting;

            } else {
                printf("Not possible sorting mode chosen.\n");
                return kErrorWrongMode;
            }
        }
    }

    return kNoError;
}

PossibleErrors handle_all_sort(LineInfo *text_ptr, TypesOfSort sorting_type) {
    assert(text_ptr != NULL);

    char *buf_ptr = NULL;
    size_t line_count = 0;
    size_t filesize = (size_t)size_of_file("textonegin.txt");

    buf_input("textonegin.txt", text_ptr, &buf_ptr, &line_count, filesize);

    FILE *file = fopen("SortedOnegin.txt", "w");
    handle_switch_sort(text_ptr, sorting_type, (int)line_count, compare_ltor);
    output_all_ltor(file, text_ptr, filesize);

    handle_switch_sort(text_ptr, sorting_type, (int)line_count, compare_rtol);
    output_all_ltor(file, text_ptr, filesize);

    output_original(file, buf_ptr);

    free(buf_ptr);
    return kNoError;
}

void handle_switch_sort(LineInfo *text_ptr, TypesOfSort sorting_type, int line_count, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);

    switch(sorting_type) {
    case (qsorting):
        qsort(text_ptr, LINECOUNT, sizeof(LineInfo), compares);
    case (bubble_sorting):
        bubble_sort(text_ptr, compares);
    case (quick_sorting):
        quick_sort(text_ptr, 0, line_count, compares);
    }
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
        return kErrorStat;
    }

    return stbuf.st_size;
}

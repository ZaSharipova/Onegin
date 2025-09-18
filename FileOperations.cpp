#include "FileOperations.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#include "AllInput.h"
#include "AllOutput.h"

PossibleErrors check_sort_mode(char *str, TypesOfSort *type) {
    assert(str  != NULL);
    assert(type != NULL);

    if (strcmp(str, "qsort") == 0) {
        *type = Global_qsorting;

    } else {
        if (strcmp(str, "bubble_sort") == 0) {
            *type = Global_bubble_sorting;

        } else {
            if (strcmp(str, "quick_sort") == 0) {
                *type = Global_quick_sorting;


            } else {
                if (strcmp(str, "insertion_sort") == 0) {
                    *type = Global_quick_sorting;
                
                } else {
                    printf("Not possible sorting mode chosen.\n");
                    
                    return kErrorWrongMode;
                }
            }
        }
    }

    return kNoError;
}

PossibleErrors handle_all_sort(TypesOfSort sorting_type, const char *filename_in, const char *filename_out) {
    assert(filename_in != NULL);
    assert(filename_out != NULL);

    char *buf_ptr = NULL;
    size_t line_count = 0;;
    size_t filesize = (size_t)size_of_file(filename_in);
    assert(filesize);

    struct LineInfo *pointer;
    buf_input(filename_in, &pointer, &buf_ptr, &line_count, filesize);

    FILE *file = fopen(filename_out, WRITE_MODE);

    handle_switch_sort(pointer, sorting_type, (int)line_count, compare_ltor);
    output_all(file, pointer, filesize, Global_direct);

    handle_switch_sort(pointer, sorting_type, (int)line_count, compare_rtol);
    output_all(file, pointer, filesize, Global_reverse);

    output_original(file, buf_ptr);

    PossibleErrors status = close_file(file);
    if (status != kNoError) {
        perror("fclse() failed");
        return kErrorClosing;
    }

    free(buf_ptr);
    free(pointer);

    return kNoError;
}

void handle_switch_sort(LineInfo *text_ptr, TypesOfSort sorting_type, int line_count, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);

    switch(sorting_type) {
    case (Global_qsorting):
        qsort(text_ptr, LINECOUNT, sizeof(LineInfo), compares);
        break;

    case (Global_bubble_sorting):
        bubble_sort(text_ptr, compares);
        break;

    case (Global_quick_sorting):
        quick_sort(text_ptr, 0, line_count, compares);
        break;

    case (Global_insertion_sorting):
        insertion_sort(text_ptr, line_count, compares);
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
        perror("stat() failed");
        return kErrorStat;
    }

    return stbuf.st_size;
}

size_t count_lines(char *buf_ptr) {
    assert(buf_ptr != NULL);

    size_t counter = 0;
    char *ptr = buf_ptr;
    while ((ptr = (strchr(ptr, '\n'))) != NULL) {
        counter++;
        ptr++;
    }

    return counter;
}
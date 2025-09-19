#include "FileOperations.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#include "AllInput.h"
#include "AllOutput.h"

PossibleErrors handle_all_sort(char *buf_ptr, LineInfo *text_ptr, TypesOfSort sorting_type, const char *filename_in, const char *filename_out, size_t line_count) {
    assert(filename_in  != NULL);
    assert(filename_out != NULL);
    assert(buf_ptr      != NULL);
    assert(text_ptr     != NULL);


    FILE *file = open_file(filename_out, WRITE_MODE);

    handle_switch_sort(text_ptr, sorting_type, (int)line_count, compare_ltor);
    output_all(file, text_ptr, Global_direct, (int)line_count);

    handle_switch_sort(text_ptr, sorting_type, (int)line_count, compare_rtol);
    output_all(file, text_ptr, Global_reverse, (int)line_count);

    output_original(file, buf_ptr);

    //output_sorted_lines(pointer, file, (int)line_count);
    
    PossibleErrors status = close_file(file);
    if (status != kNoError) {
        perror("fclse() failed");
        return kErrorClosing;
    }

    free(buf_ptr);

    return kNoError;
}

void handle_switch_sort(LineInfo *text_ptr, TypesOfSort sorting_type, int line_count, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);

    switch(sorting_type) {
    case (Global_qsorting):
        qsort(text_ptr, line_count, sizeof(LineInfo), compares);
        break;

    case (Global_bubble_sorting):
        bubble_sort(text_ptr, compares);
        break;

    case (Global_quick_sorting):
        quick_sort(text_ptr, 0, line_count, compares);
        break;

    case (Global_insertion_sorting):
        insertion_sort(text_ptr, 0, line_count, compares);
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
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileOperations.h"
#include "ParseInput.h"
#include "AllInput.h"

int main(int argc, char *argv[]) {
    const char *filename_in = "TextOnegin.txt";
    const char *filename_out = "SortedOnegin.txt";
    TypesOfSort sort_mode = Global_qsorting;

    PossibleErrors err = parse_argv(argc, argv, &sort_mode, &filename_in, &filename_out);
    if (err != kNoError) {
        return err;
    }

    FILE *file = open_file(filename_in, READ_MODE);
    if (file == NULL) {
        perror("fopen() failed");
        return kErrorOpening;
    }

    size_t line_count = 0;
    size_t filesize = 0;
    char *buf_ptr = NULL;

    err = buf_input(filename_in, &buf_ptr, &line_count, &filesize);

    LineInfo *text_ptr = (struct LineInfo *) calloc(line_count + 1, sizeof(LineInfo));

    err = handle_parse_buf(text_ptr, buf_ptr, filesize, file);
    if (err != kNoError) {
        free(text_ptr);
        return err;
    }

    err = handle_all_sort(buf_ptr, text_ptr, sort_mode, filename_in, filename_out, line_count);
    if (err != kNoError) {
        free(text_ptr);
        return err;
    }

    free(text_ptr);

    return kNoError;
}
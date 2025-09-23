#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileOperations.h"
#include "ParseInput.h"
#include "AllInput.h"

int main(int argc, char *argv[]) {
    struct ArgumentModes flags = {.filename_in = "TextOnegin.txt", 
        .filename_out = "SortedOnegin.txt", .sort_mode = TypesOfSortQsort};
    struct FileInfo file_info = {.buf_ptr = NULL, .text_ptr = NULL, 
        .filesize = 0, .count_lines = 0};

    PossibleErrors err = parse_argv(argc, argv, &flags);
    if (err != kNoError) {
        return err;
    }

    FILE *file = open_file(flags.filename_in, READ_MODE);
    if (file == NULL) {
        return kErrorOpening;
    }

    err = handle_buf_read(flags.filename_in, &file_info);

    err = handle_all_sort(&file_info, flags); 
    if (err != kNoError) {
        free(file_info.text_ptr);
        return err;
    }

    free(file_info.text_ptr);

    return kNoError;
}
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileOperations.h"

int main(int argc, char *argv[]) {
    TypesOfSort sort_mode = qsorting;
    PossibleErrors err = parse_argv(argc, argv, &sort_mode);
    if (err != kNoError) {
        return err;
    }

    struct LineInfo *text_ptr = (struct LineInfo *) calloc(LINECOUNT + 1, sizeof(LineInfo));
    
    err = handle_all_sort(text_ptr, sort_mode);
    if (err != kNoError) {
        return err;
    }

    free(text_ptr);
    return kNoError;
}
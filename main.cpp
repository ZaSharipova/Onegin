#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileOperations.h"
#include "AllInput.h"

int main(int argc, char *argv[]) {
    const char *filename_in = "textonegin.txt";
    const char *filename_out = "SortedOnegin.txt";

    TypesOfSort sort_mode = Global_qsorting;
    PossibleErrors err = parse_argv(argc, argv, &sort_mode, &filename_in, &filename_out);
    if (err != kNoError) {
        return err;
    }
    
    err = handle_all_sort(sort_mode, filename_in, filename_out);
    if (err != kNoError) {
        return err;
    }

    return kNoError;
}
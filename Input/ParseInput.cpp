#include "ParseInput.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

PossibleErrors parse_argv(int argc, char *argv[], ArgumentModes *flags) {
    assert(argv  != NULL);
    assert(flags != nullptr);

    size_t pos = 1;
    PossibleErrors err = kNoError;

    if (argc > 1) {
        err = parse_arguments(argc, argv, pos, flags);
        if (err != kNoError) {
            return err;
        }
        
    }

    return kNoError;
}

PossibleErrors parse_arguments(int argc, char *argv[], size_t pos, ArgumentModes *flags) {
    assert(argv  != NULL);
    assert(flags != NULL);

    size_t i = pos;
    //size_t last_of_positions = pos + 6;

    while (i < (size_t)argc) {
        if (parse_in_out(argv, i, IN_MODE, &(flags->filename_in))) {
            i += 2;

        } else {
            if (parse_in_out(argv, i, OUT_MODE, &(flags->filename_out))) {
                i += 2;

            } else {
                if (parse_sorting_modes(argv, i, &(flags->sort_mode)) == kNoError) {
                    i += 2;

                } else {
                    printf("Wrong mode %s.\n", argv[i]);
                    return kErrorParsing;
                }
            }
        }
    }

    return kNoError;
}

bool parse_in_out(char *argv[], size_t pos, const char *mode, const char **filename) {
    assert(argv     != NULL);
    assert(mode     != NULL);
    assert(filename != NULL);

    if (strcmp(argv[pos], mode) == 0) {
        *filename = argv[pos + 1];

        return true;
    }

    return false;

}

PossibleErrors parse_sorting_modes(char *argv[], size_t pos, TypesOfSort *sort_mode) {
    assert(argv      != NULL);
    assert(sort_mode != NULL);

    if (strcmp(argv[pos], SORT_MODE) == 0) {
        pos++;
        PossibleErrors err = check_sort_mode(argv[pos], sort_mode);
        return err;

    } 
    
    return kNoSolution;
}

PossibleErrors check_sort_mode(char *str, TypesOfSort *sort_mode) {
    assert(str       != NULL);
    assert(sort_mode != NULL);

    if (strcmp(str, "qsort") == 0) {
        *sort_mode = TypesOfSortQsort;

    } else if (strcmp(str, "bubble_sort") == 0) {
        *sort_mode = TypesOfSortBubble;

    } else if (strcmp(str, "quick_sort") == 0) {
        *sort_mode = TypesOfSortMyQuick;

    } else if (strcmp(str, "insertion_sort") == 0) {
        *sort_mode = TypesOfSortInsertion;
                
    } else {
        printf("Not possible sorting mode chosen.\n");
        return kErrorWrongMode;
    }

    return kNoError;
}
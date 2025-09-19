#include "ParseInput.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

PossibleErrors parse_argv(int argc, char *argv[], TypesOfSort *sorting_type, const char **filename_in, const char **filename_out) {
    assert(argv         != NULL);
    assert(sorting_type != nullptr);

    size_t pos = 1;
    PossibleErrors err = kNoError;

    if (argc > 1) {
        err = parse_arguments(argc, argv, pos, filename_in, filename_out, sorting_type);
        if (err != kNoError) {
            return err;
        }
        
    }

    return kNoError;
}

PossibleErrors parse_arguments(int argc, char *argv[], size_t pos, const char **filename_in, const char **filename_out, TypesOfSort *sorting_modes) {
    assert(argv         != NULL);
    assert(filename_in  != NULL);
    assert(filename_out != NULL);

    size_t i = pos;
    //size_t last_of_positions = pos + 6;

    while (i < (size_t)argc) {
        if (parse_in_out(argv, i, IN_MODE, filename_in)) {
            i += 2;

        } else {
            if (parse_in_out(argv, i, OUT_MODE, filename_out)) {
                i += 2;

            } else {
                if (parse_sorting_modes(argv, i, sorting_modes) == kNoError) {
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

PossibleErrors parse_sorting_modes(char *argv[], size_t pos, TypesOfSort *sorting_modes) {
    assert(argv          != NULL);
    assert(sorting_modes != NULL);

    if (strcmp(argv[pos], SORT_MODE) == 0) {
        pos++;
        PossibleErrors err = check_sort_mode(argv[pos], sorting_modes);

        return err;

    } 
    
    return kNoSolution;
}

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
#ifndef CONSTANTS_AND_STRUCTS_H_
#define CONSTANTS_AND_STRUCTS_H_

#include <stdio.h>

#define LINECOUNT 5332
#define STROKESIZE 48

enum PossibleErrors {
    kNoError       = 0,
    kErrorOpening  = -1,
    kErrorClosing  = -2,
    kErrorStat     = -3,
    kErrorWrite    = -4,
    kErrorWrongMode = -5,
    kErrorParsing   = -6,
};

struct Limits {
    size_t left;
    size_t right;
};

struct LineInfo {
    char *start_ptr;
    char *end_ptr;
    char *start_ptr_alpha;
    char *end_ptr_alpha;
    size_t size;
};

enum TypesOfSort {
    qsorting,
    bubble_sorting,
    quick_sorting,
};

#endif //CONSTANTS_AND_STRUCTS_H_
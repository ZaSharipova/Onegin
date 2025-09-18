#ifndef CONSTANTS_AND_STRUCTS_H_
#define CONSTANTS_AND_STRUCTS_H_

#include <stdio.h>

#define LINECOUNT 5332
#define STROKESIZE 48

#define IN_MODE "--in"
#define OUT_MODE "--out"

#define SORT_MODE "--sort"

#define READ_MODE "r"
#define WRITE_MODE "w"

enum PossibleErrors {
    kNoError        = 0,
    kErrorOpening   = -1,
    kErrorClosing   = -2,
    kErrorStat      = -3,
    kErrorWrite     = -4,
    kErrorWrongMode = -5,
    kErrorParsing   = -6,
    kNoSolution     = -7,
};

struct LineInfo {
    char *start_ptr;
    char *end_ptr;
    char *start_ptr_alpha;
    char *end_ptr_alpha;
    size_t size;
};

enum TypesOfSort {
    Global_qsorting,
    Global_bubble_sorting,
    Global_quick_sorting,
    Global_insertion_sorting,
};

enum CompareTypes {
    Global_direct,
    Global_reverse,
};

#endif //CONSTANTS_AND_STRUCTS_H_
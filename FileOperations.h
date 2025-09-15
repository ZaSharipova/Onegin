#ifndef FILE_OPERATIONS_H_
#define FILE_OPERATIONS_H_

#include <stdio.h>

#ifndef FILESIZE
#define FILESIZE 5332
#endif

#ifndef STROKESIZE
#define STROKESIZE 48
#endif

enum PossibleErrors {
    kNoError      = 0,
    kErrorOpening = -1,
    kErrorClosing = -2,
};

FILE *open_file(const char *filename, const char *mode);
PossibleErrors close_file(FILE *file);

void swap_lines_with_copies(char *text1, char *text2);
int swap_lines_with_char(char text[][STROKESIZE], size_t pos1, size_t pos2);
int swap_char(char *char1, char *char2);
void swap_pointers(char **ptr1, char **ptr2);
void swap_all_with_char(char text[][STROKESIZE]);
int sort_with_strcpy(char text[][STROKESIZE]);
void swap_blocks(char *text1, char *text2, size_t n);
void swap_all_with_pointers(char *text[]);
int Mstrcmp(const char *str1, const char *str2);

size_t partition(char *text[], size_t l, size_t r);
void quick_sort(char *text[], size_t l, size_t r);
//static inline void swap_pointers(char **a, char **b);

void output_sorted_onegin(char *text[], size_t size);

#endif //FILE_OPERATIONS_H_
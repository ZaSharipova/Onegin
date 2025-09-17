#ifndef SORTINGS_H_
#define SORTINGS_H_

#include "ConstantsAndStructs.h"
#include <stdio.h>

void swap_lineinfo(struct LineInfo *arr1, struct LineInfo *arr2);
int partition(struct LineInfo *text_ptr, int l, int r, int (*compares)(const void *, const void *));
void quick_sort(struct LineInfo *text_ptr, int l, int r, int (*compares)(const void *, const void *));

void bubble_sort (LineInfo *text_ptr);
int Mstrcmp_LtoR(char *str1, char *str2, char *end_ptr1, char *end_ptr2);
int Mstrcmp_RtoL(char *str1, char *str2, char *start_ptr1, char *start_ptr2);
int compare_LtoR(const void *a, const void *b);
int compare_RtoL(const void *a, const void *b);

int compare_bubble_LtoR (const void *A, const void *B);

#endif //SORTINGS_H_
#ifndef SORTINGS_H_
#define SORTINGS_H_

#include "ConstantsAndStructs.h"

#include <stdio.h>

void swap_lineinfo(struct LineInfo *arr1, struct LineInfo *arr2);
int partition(struct LineInfo *text_ptr, int l, int r, int (*compares)(const void *, const void *));
void quick_sort(struct LineInfo *text_ptr, int l, int r, int (*compares)(const void *, const void *));
void bubble_sort(struct LineInfo *text_ptr, int line_count, int (*compares)(const void *, const void *));
void insertion_sort(struct LineInfo *text_ptr, int left, int right, int (*compares)(const void *, const void *));
void quick_sort_with_stack(struct LineInfo *text_ptr, int line_count, int left, int right, int (*compares)(const void*, const void*));

int Mstrcmp_ltor(char *start_ptr1, char *start_ptr2, char *end_ptr1, char *end_ptr2);
int Mstrcmp_rtol(char *end_ptr1, char *end_ptr2, char *start_ptr1, char *start_ptr2);
int compare_ltor(const void *text1, const void *text2);
int compare_rtol(const void *text1, const void *text2);

void compare_two_pointers(struct LineInfo *str1, struct LineInfo *str2, int (*compare)(const void *, const void *));
void compare_three_pointers(struct LineInfo *text_ptr, int left, int right, int (*compares)(const void *, const void *));

int rand_index(int left, int right);
#endif //SORTINGS_H_
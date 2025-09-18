#ifndef FILE_OPERATIONS_H_
#define FILE_OPERATIONS_H_

#include <stdio.h>
#include "ConstantsAndStructs.h"
PossibleErrors parse_argv(int argc, char *argv[], TypesOfSort *type);
PossibleErrors check_sort_mode(char *str, TypesOfSort *sorting_type);
PossibleErrors handle_all_sort(LineInfo *text_ptr, TypesOfSort sorting_type);
void handle_switch_sort(LineInfo *text_ptr, TypesOfSort sorting_type, int line_count, int (*compares)(const void *, const void *));

FILE *open_file(const char *filename, const char *mode);
PossibleErrors close_file(FILE *file);

long long size_of_file(const char *filename);

#endif //FILE_OPERATIONS_H_
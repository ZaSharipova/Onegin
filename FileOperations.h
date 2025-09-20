#ifndef FILE_OPERATIONS_H_
#define FILE_OPERATIONS_H_

#include <stdio.h>

#include "ConstantsAndStructs.h"
#include "Sortings.h"

PossibleErrors check_sort_mode(char *str, TypesOfSort *sorting_type);

PossibleErrors handle_all_sort(FileInfo *file_info, ArgumentModes flags);
void handle_switch_sort(FileInfo *file_info, TypesOfSort sort_mode, int (*compares)(const void *, const void *));

FILE *open_file(const char *filename, const char *mode);
PossibleErrors close_file(FILE *file);

long long size_of_file(const char *filename);
size_t count_lines(char *buf_ptr);


//---------------------------------------------------------------------------
//! @brief Checks if a line consists only of whitespace.
//!
//! This function examines a line of given length and determines if all
//! characters are whitespace (spaces, tabs, etc.).
//!
//! @param[in] start     Pointer to the start of the line.
//! @param[in] line_size Length of the line in characters.
//!
//! @return 1 if the line is blank (only whitespace), 0 otherwise.
//---------------------------------------------------------------------------
int is_blank_line(const char* start, size_t line_size);
#endif //FILE_OPERATIONS_H_
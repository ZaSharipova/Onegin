#ifndef FILE_OPERATIONS_H_
#define FILE_OPERATIONS_H_

#include <stdio.h>
#include "ConstantsAndStructs.h"

int pointers_text(struct LineInfo *text_ptr);

FILE *open_file(const char *filename, const char *mode);
PossibleErrors close_file(FILE *file);

long long size_of_file(const char *filename);
char *read_to_buf(const char *filename, FILE *file);
size_t parse_buf(char *buf, struct LineInfo *text_ptr);
PossibleErrors buf_input(const char *filename, struct LineInfo *text_ptr, char **buf_ptr, size_t *line_count);
void output_with_buf(struct LineInfo *text_ptr, FILE *file);
void output_original_text(FILE *file, char *buf);

#endif //FILE_OPERATIONS_H_
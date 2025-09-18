#ifndef ALL_INPUT_H_
#define ALL_INPUT_H_

#include "ConstantsAndStructs.h"

PossibleErrors parse_argv(int argc, char *argv[], TypesOfSort *sorting_type);
char *read_to_buf(const char *filename, FILE *file, size_t filesize);
size_t parse_buf(char *buf, struct LineInfo *text_ptr, size_t bufsize);
PossibleErrors buf_input(const char *filename, struct LineInfo *text_ptr, char **buf_ptr, size_t *line_count, size_t filesize);

#endif //ALL_INPUT_H_
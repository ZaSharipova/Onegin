#ifndef ALL_INPUT_H_
#define ALL_INPUT_H_

#include "ConstantsAndStructs.h"

PossibleErrors parse_argv(int argc, char *argv[], TypesOfSort *sorting_type, const char **filename_in, const char **filename_out);
char *read_to_buf(const char *filename, FILE *file, size_t filesize);
size_t parse_buf(char *buf, struct LineInfo *text_ptr, size_t bufsize);
PossibleErrors buf_input(const char *filename, LineInfo **text_ptr, char **buf_ptr, size_t *line_count, size_t filesize);
PossibleErrors handle_parse_buf(struct LineInfo *text_ptr, char *buf_ptr, size_t filesize, FILE *file);
PossibleErrors parse_arguments(int argc, char *argv[], size_t pos, const char **filename_in, const char **filename_out, TypesOfSort *sorting_modes);
PossibleErrors parse_sorting_modes(char *argv[], size_t pos, TypesOfSort *sorting_modes);
bool parse_in_out(char *argv[], size_t pos, const char *mode, const char **filename);

#endif //ALL_INPUT_H_
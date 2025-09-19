#ifndef ALL_INPUT_H_
#define ALL_INPUT_H_

#include "ConstantsAndStructs.h"

char *read_to_buf(const char *filename, FILE *file, size_t filesize);
size_t parse_buf(char *buf, struct LineInfo *text_ptr, size_t bufsize);
PossibleErrors buf_input(const char *filename, char **buf_ptr, size_t *line_count, size_t *filesize);
PossibleErrors handle_parse_buf(struct LineInfo *text_ptr, char *buf_ptr, size_t filesize, FILE *file);

#endif //ALL_INPUT_H_
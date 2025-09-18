#ifndef ALL_OUTPUT_H_
#define ALL_OUTPUT_H_

#include "ConstantsAndStructs.h"

PossibleErrors output_with_buf(struct LineInfo *text_ptr, FILE *file, size_t filesize);
PossibleErrors output_original_text(FILE *file, char *buf);

void output_all_ltor(FILE *file, LineInfo *text_ptr, size_t filesize);
void output_all_rtol(FILE *file, LineInfo *text_ptr, size_t filesize);
void output_original(FILE *file, char *buf_ptr);

#endif //ALL_OUTPUT_H_
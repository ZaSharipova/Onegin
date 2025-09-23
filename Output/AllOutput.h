#ifndef ALL_OUTPUT_H_
#define ALL_OUTPUT_H_

#include "ConstantsAndStructs.h"

PossibleErrors output_sorted_lines(FILE *file, struct LineInfo *text_ptr, int line_count);
PossibleErrors output_with_buf(struct LineInfo *text_ptr, FILE *file, size_t filesize, int line_count);
PossibleErrors output_original_text(FILE *file, char *buf);

void output_sorted(FILE *file, struct LineInfo *text_ptr, CompareTypes compare_mode, int line_count);
//void output_all_rtol(FILE *file, LineInfo *text_ptr, size_t filesize);
void output_original(FILE *file, char *buf_ptr, int line_count);

#endif //ALL_OUTPUT_H_
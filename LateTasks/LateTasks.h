#ifndef LATE_TASKS_H_
#define LATE_TASKS_H_

#include "ConstantsAndStructs.h"
#include <stdio.h>

int square_text(void);
size_t read_lines(char **text_ptr, FILE *file);

void swap_lines_with_copies(char *text1, char *text2);
int swap_lines_with_char(char text[][STROKESIZE], size_t pos1, size_t pos2);
void swap_two_chars(char *char1, char *char2);
void swap_pointers(char **ptr1, char **ptr2);
void swap_all_with_pointers(char *text[]);
void swap_blocks(char *text1, char *text2, size_t n);
void swap_all_with_char(char text[][STROKESIZE]);
void sort_with_strcpy(char text[][STROKESIZE]);

void output_sorted_onegin(struct LineInfo *file_ptr, size_t size);
#endif //LATE_TASKS_H_
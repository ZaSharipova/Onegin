#include "AllOutputText.h"

#include <stdio.h>
#include <assert.h>

void print_sorted_LtoR_label(FILE *file) {
    assert(file != NULL);
    
    fprintf(file, "---------------------------------------------\n");
    fprintf(file, "          Sorted LtoR Onegin:\n");
    fprintf(file, "---------------------------------------------\n");
}

void print_sorted_RtoL_label(FILE *file) {
    assert(file != NULL);

    fprintf(file, "---------------------------------------------\n");
    fprintf(file, "           Sorted RtoL Onegin:\n");
    fprintf(file, "---------------------------------------------\n");
}

void print_original_label(FILE *file) {
    assert(file != NULL);

    fprintf(file, "---------------------------------------------\n");
    fprintf(file, "         Original Onegin text:\n");
    fprintf(file, "---------------------------------------------\n");
}
#include "AllOutput.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "AllOutputText.h"

PossibleErrors output_with_buf(struct LineInfo *text_ptr, FILE *file, size_t filesize) {
    assert(text_ptr != NULL);
    assert(file     != NULL);

    char *buf_out = (char *) calloc(filesize + LINECOUNT + 1, sizeof(char));
    assert(buf_out != NULL);
    char *ptr = buf_out;

    for (size_t pos = 0; pos < LINECOUNT; pos++) {

        memcpy(ptr, text_ptr[pos].start_ptr, text_ptr[pos].size);
        ptr += text_ptr[pos].size;
        *ptr = '\n';
        ptr++;
    }
    *ptr = '\0';

    size_t size = strlen(buf_out);

    size_t status = fwrite(buf_out, sizeof(char), size, file);
    if (status != size) {
        perror("fwrite() failed");
        return kErrorWrite;
    }

    free(buf_out);
    return kNoError;
} 

PossibleErrors output_original_text(FILE *file, char *buf) {
    assert(file != NULL);

    size_t size = strlen(buf);

    size_t status = fwrite(buf, sizeof(char), size, file);
    if (status != size) {
        perror("fwrite() failed");
        return kErrorWrite;
    }

    fclose(file);
    return kNoError;
}

void output_all_ltor(FILE *file, LineInfo *text_ptr, size_t filesize) {
    assert(file     != NULL);
    assert(text_ptr != NULL);

    print_sorted_LtoR_label(file);
    output_with_buf(text_ptr, file, filesize);
    printf("Sorting  1 done. It is from line %d\n", 4);
}

void output_all_rtol(FILE *file, LineInfo *text_ptr, size_t filesize) {
    assert(file     != NULL);
    assert(text_ptr != NULL);

    print_sorted_RtoL_label(file);
    output_with_buf(text_ptr, file, filesize);
    printf("Sorting  2 done. You can see it from line %d\n", LINECOUNT + 7);
}

void output_original(FILE *file, char *buf_ptr) {
    assert(file != NULL);
    assert(buf_ptr != NULL);

    print_original_label(file);
    output_original_text(file, buf_ptr);
    printf("Original Text is from line %d\n", LINECOUNT * 2 + 10);
}
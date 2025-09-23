#include "AllOutput.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "AllOutputText.h"

PossibleErrors output_sorted_lines(FILE *file, struct LineInfo *text_ptr, int line_count) {
    assert(file     != NULL);
    assert(text_ptr != NULL);

    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%.*s\n", (int)text_ptr[i].size, text_ptr[i].start_ptr);
    }
    return kNoError;
}

PossibleErrors output_with_buf(struct LineInfo *text_ptr, FILE *file, size_t filesize, int line_count) {
    assert(text_ptr != NULL);
    assert(file     != NULL);

    size_t size = filesize + (size_t)line_count + 1;

    char *buf_out = (char *) calloc(size, sizeof(char));
    assert(buf_out != NULL);
    char *ptr = buf_out; 

    for (size_t pos = 0; pos < (size_t)line_count; pos++) {

        memcpy(ptr, text_ptr[pos].start_ptr, text_ptr[pos].size);
        ptr += text_ptr[pos].size;
        *ptr = '\n';
        ptr++;
    }
    *ptr = '\0';

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

    return kNoError;
}

void output_sorted(FILE *file, struct LineInfo *text_ptr, CompareTypes compare_mode, int line_count) {
    assert(file     != NULL);
    assert(text_ptr != NULL);

    if (compare_mode == CompareTypesDirect) {
        print_sorted_LtoR_label(file);
        printf("Sorting  1 done. It is from line %d\n", 4);

    } else {
        print_sorted_RtoL_label(file);
        printf("Sorting  2 done. You can see it from line %d\n", line_count + 7);
    }

    output_sorted_lines(file, text_ptr, line_count);
}

// void output_all_rtol(FILE *file, LineInfo *text_ptr, size_t filesize) {
//     assert(file     != NULL);
//     assert(text_ptr != NULL);

//     print_sorted_RtoL_label(file);
//     output_with_buf(text_ptr, file, filesize);
//     printf("Sorting  2 done. You can see it from line %d\n", LINECOUNT + 7);
// }

void output_original(FILE *file, char *buf_ptr, int line_count) {
    assert(file != NULL);
    assert(buf_ptr != NULL);

    print_original_label(file);
    output_original_text(file, buf_ptr);
    printf("Original Text is from line %d\n", line_count * 2 + 10);
}
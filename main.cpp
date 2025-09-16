#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileOperations.h"

int square_text(void) {

    FILE *file = open_file("OneginText.txt", "r");
    if (file == NULL) {
        perror("fopen() failed");
    }

    char text[FILESIZE][STROKESIZE];
    size_t i = 0;
    while (i < FILESIZE) {
        fgets(text[i], STROKESIZE, file);
        if (text[i][0] == '\n') {
            i--;
        }
        i++;
    }

    swap_all_with_char(text);

    i = 0;
    while (i < FILESIZE) {
        printf("%s\n", text[i]);
        i++;
    }

    PossibleErrors err = close_file(file);
    if (err != kNoError) {
        perror("fclose() failed");
    }

    return kNoError;
}

size_t read_lines(char **text_ptr, FILE *file) {
    assert(text_ptr != NULL);
    assert(file != NULL);
    
    char *buf = (char *) calloc(STROKESIZE + 1, sizeof(char));
    assert(buf != NULL);

    size_t count = 0;

    while (count < FILESIZE) {
        char *ptr1 = fgets(buf, STROKESIZE, file);
        if (ptr1 == NULL) {
            break;
        }

        char *ptr = strdup(buf);
        assert(ptr != NULL);
        text_ptr[count++] = ptr;
    }

    free(buf);
    return count;
}

int pointers_text(char **text_ptr) {
    assert(text_ptr != NULL);

    buf_input("textonegin.txt", text_ptr);

    size_t line_count = FILESIZE;

    quick_sort(text_ptr, 0, line_count - 1);
    output_sorted_onegin(text_ptr, line_count);

   FILE *file = fopen("SortedOnegin.txt", "w");

    output_with_buf(text_ptr, file);
    for (size_t j = 0; j < line_count; j++) {
        free(text_ptr[j]);
    }

    return kNoError;
}

int main(void) {
    char ** text_ptr = (char **) calloc(FILESIZE + 1, sizeof(char *));
    
    int err = pointers_text(text_ptr);
    free(text_ptr);
    return err;
}
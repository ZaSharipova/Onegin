#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileOperations.h"

int square_text(void) {

    FILE *file = open_file("OneginText.txt", "r");
    if (file == NULL) {
        perror("fopen() failed");
    }

    char text[28][46];
    size_t i = 0;
    while (i < 29) {
        fgets(text[i], 45, file);
        if (text[i][0] == '\n') {
            i--;
        }
        i++;
    }

    swap_all_with_char(text);

    i = 0;
    while (i < 28) {
        printf("%s\n", text[i]);
        i++;
    }

    PossibleErrors err = close_file(file);
    if (err != kNoError) {
        perror("fclose() failed");
    }

    return kNoError;
}

int read_lines(char **text_ptr, FILE *file) {
    assert(text_ptr != NULL);
    assert(file != NULL);
    
    char *buf = (char *) calloc(46, sizeof(char));
    assert(buf != NULL);

    size_t i = 0;
    int count = 0;

    while (i < 29 && count < 28) {
        fgets(buf, 46, file);
        if (buf[0] == '\n' || buf[1] == '\n') {
            continue;
        } else {
            char * ptr = strdup(buf);
            text_ptr[count] = ptr;
            assert(text_ptr[count] != NULL);

            count++;
        }
        i++;
    }

    free(buf);
    return 0;
}

int pointers_text(char **text_ptr) {
    assert(text_ptr != NULL);

    FILE *file = open_file("OneginText.txt", "r");
    if (file == NULL) {
        return kErrorOpening;
    }

    read_lines(text_ptr, file); //TODO считывание в буфер -> затем уже в массив
    //strswap_pointers(text_ptr, 28);
    quick_sort(text_ptr, 0, 28);
    for (size_t i = 0; i < 28; i++) {
        printf("%s\n", text_ptr[i]);
    }
    printf("\n\n\n");

    for (int j = 0; j < 28; j++) {
        free(text_ptr[j]);
    }

    PossibleErrors err = close_file(file);
    if (err != kNoError) {
        return err;
    }

    return kNoError;
}

int main(void) {
    char ** text_ptr = (char **) calloc(28, sizeof(char *));
    //char *text_ptr[28];
    // for (int i = 0; i < 28; i++) {
    //     text_ptr[i] = "10000";
    // }
    
    int err = pointers_text(text_ptr);
    free(text_ptr);
    return err;
}
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
            break;  // конец файла или ошибка
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

    FILE *file = open_file("textonegin.txt", "r");
    if (file == NULL) {
        return kErrorOpening;
    }

    size_t line_count = read_lines(text_ptr, file); //TODO считывание в буфер -> затем уже в массив
    // for (size_t i = 0; i < line_count; i++) {
    //     printf("%s\n", text_ptr[i]);
    // }
    //strswap_pointers(text_ptr, 28);
    quick_sort(text_ptr, 0, line_count - 1);
    // for (size_t i = 0; i < line_count; i++) {
    //     printf("%s\n", text_ptr[i]);
    // }
    // printf("\n\n\n");
    output_sorted_onegin(text_ptr, line_count);

    for (size_t j = 0; j < line_count; j++) {
        free(text_ptr[j]);
    }

    PossibleErrors err = close_file(file);
    if (err != kNoError) {
        return err;
    }

    return kNoError;
}

int main(void) {
    char ** text_ptr = (char **) calloc(FILESIZE + 1, sizeof(char *));
    //char *text_ptr[28];
    // for (int i = 0; i < 28; i++) {
    //     text_ptr[i] = "10000";
    // }
    
    int err = pointers_text(text_ptr);
    free(text_ptr);
    return err;
}
#include "LateTasks.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "ConstantsAndStructs.h"
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

void swap_lines_with_copies(char *text1, char *text2) {
    assert(text1 != NULL);
    assert(text2 != NULL);

    char buf[50];
    strcpy(buf, text1);
    strcpy(text1, text2);
    strcpy(text2, buf);
}

int swap_lines_with_char(char text[][STROKESIZE], size_t pos1, size_t pos2) {
    assert(text != NULL);

    for (size_t size = 0; size < STROKESIZE; size++) {
        swap_two_chars(&text[pos1][size], &text[pos2][size]);
    }

    return kNoError;
}

void swap_two_chars(char *char1, char *char2) {
    assert(char1 != NULL);
    assert(char2 != NULL);

    char buf = *char1;
    *char1 = *char2;
    *char2 = buf;
}

void swap_pointers(char **ptr1, char **ptr2) { //
    assert(ptr1 != NULL);
    assert(ptr2 != NULL);

    char *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void swap_all_with_pointers(char *text[]) {
    assert(text != NULL);

    for (size_t index_sort = 0; index_sort < FILESIZE; index_sort++) {
        int sorted = 0;
        for (size_t pos_compared = 0; pos_compared < FILESIZE - index_sort - 1; pos_compared++) {
            if (strcmp(text[pos_compared], text[pos_compared + 1]) > 0) {
                swap_pointers(&text[pos_compared], &text[pos_compared + 1]);
                sorted = 1;
            }
        }
        if (sorted == 0) {
            break;
        }
    }
}

void swap_all_with_char(char text[][STROKESIZE]) {
    assert(text != NULL);

    for (size_t index_sort = 0; index_sort < FILESIZE; index_sort++) {
        int sorted = 0;

        for (size_t pos_compared = 0; pos_compared < FILESIZE - index_sort - 1; pos_compared++) {
            if (strcmp(text[pos_compared], text[pos_compared + 1]) > 0) {
                swap_lines_with_char(text, pos_compared, pos_compared + 1);
                sorted = 1;
            }
        }

        if (sorted == 0) {
            break;
        }
    }
}

void swap_blocks(char *text1, char *text2, size_t n) {
    assert(text1 != NULL);
    assert(text2 != NULL);

    size_t count = n / sizeof(unsigned long long);
    unsigned long long *pa = (unsigned long long *)text1; //TODO change names
    unsigned long long *pb = (unsigned long long *)text2;

    for (size_t pos = 0; pos < count; pos++) {
        unsigned long long temp = pa[pos];
        pa[pos] = pb[pos];
        pb[pos] = temp;
    }

    count *= sizeof(unsigned long long);
    while (count < STROKESIZE) {
        swap_two_chars(&text1[count], &text2[count]);
        count++;
    }
}


void sort_with_strcpy(char text[][STROKESIZE]) {
    assert(text != NULL);

    for (size_t index_sort = 0; index_sort < FILESIZE; index_sort++) {
        int sorted = 0;

        for (size_t pos_compared = 0; pos_compared < FILESIZE - index_sort - 1; pos_compared++) {
            if (strcmp(text[pos_compared], text[pos_compared + 1]) > 0) {
                swap_lines_with_copies(text[pos_compared], text[pos_compared + 1]);
                sorted = 1;
            }
        }

        if (sorted == 0) {
            break;
        }
    }
}


void output_sorted_onegin(struct LineInfo *text, size_t size) {
    assert(text != NULL);

    FILE *file = open_file("SortedOnegin.txt", "w");
    if (file == NULL) {
        perror("fopen() failed");
    }

    for (size_t pos = 0; pos < size; pos++) {
        fwrite(text[pos].start_ptr, sizeof(char), text[pos].size, file);
        fputc('\n', file);
    }

    PossibleErrors err = close_file(file);
    if (err != kNoError) {
        perror("fclose() failed");
    }
    printf("Sorted: done\n");
}
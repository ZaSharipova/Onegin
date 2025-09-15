#include "FileOperations.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

FILE *open_file(const char *filename, const char *mode) {
    assert(filename != NULL);
    assert(mode     != NULL);

    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        return NULL;
    }

    return file;
}

PossibleErrors close_file(FILE *file) {
    assert(file != NULL);
    assert(file != stdin);
    assert(file != stdout);

    int status = fclose(file);
    if (status != 0) {
        return kErrorClosing;
    }

    return kNoError;
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
        swap_char(&text[pos1][size], &text[pos2][size]); // с помощью чаров
    }

    return kNoError;
}

int swap_char(char *char1, char *char2) {
    assert(char1 != NULL);
    assert(char2 != NULL);

    char buf = *char1;
    *char1 = *char2;
    *char2 = buf;
    return kNoError;
}

void swap_pointers(char **ptr1, char **ptr2) { //
    assert(ptr1 != NULL);
    assert(ptr2 != NULL);

    char *tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void swap_all_with_char(char text[][STROKESIZE]) {
    assert(text != NULL);

    for (size_t pos = 0; pos < FILESIZE; pos++) {
        int sorted = 0;
        for (size_t j = 0; j < FILESIZE - pos - 1; j++) {
            if (strcmp(text[j], text[j + 1]) > 0) {
                swap_lines_with_char(text, j, j + 1);
                sorted = 1;
            }
        }

        if (sorted == 0) {
            break;
        }
    }
}

void swap_all_with_pointers(char *text[]) {
    assert(text != NULL);

    for (size_t i = 0; i < FILESIZE; i++) {
        int sorted = 0;
        for (size_t j = 0; j < FILESIZE - i - 1; j++) {
            if (strcmp(text[j], text[j + 1]) > 0) {
                swap_pointers(&text[j], &text[j + 1]);
                sorted = 1;
            }
        }
        if (sorted == 0) {
            break;
        }
    }
}

int sort_with_strcpy(char text[][STROKESIZE]) {
    assert(text != NULL);

    for (size_t i = 0; i < FILESIZE; i++) {
        int sorted = 0;
        for (size_t j = 0; j < FILESIZE - i - 1; j++) {
            if (strcmp(text[j], text[j + 1]) > 0) {
                swap_lines_with_copies(text[j], text[j + 1]); // с помощью копирования строк полностью
                sorted = 1;
            }
        }

        if (sorted == 0) {
            break;
        }
    }
    return 0;
}

size_t partition(char *text[], size_t left, size_t right) {
    assert(text != NULL);

    size_t mid = (left + right) / 2;
    char *pivot = text[mid];

    while (1) {
        while (Mstrcmp(text[left], pivot) < 0) left++;
        while (Mstrcmp(text[right], pivot) > 0) right--;

        if (left >= right) return right;

        swap_pointers(&text[left], &text[right]);
        left++;
        if (right > 0) right--;
    }
}

void quick_sort(char *text[], size_t left, size_t right) {
    if (left >= right) return;

    size_t sep = partition(text, left, right);

    if (sep > left) quick_sort(text, left, sep);
    if (sep + 1 < right) quick_sort(text, sep + 1, right); // todo стэк
}

void swap_blocks(char *text1, char *text2, size_t n) { //TODO проверить работу
    assert(text1 != NULL);
    assert(text2 != NULL);

    size_t count = n / sizeof(unsigned long long);
    unsigned long long *pa = (unsigned long long *)text1;
    unsigned long long *pb = (unsigned long long *)text2;

    for (size_t i = 0; i < count; i++) {
        unsigned long long temp = pa[i];
        pa[i] = pb[i];
        pb[i] = temp;
    }

    count *= sizeof(unsigned long long);
    while (count < STROKESIZE) {
        swap_char(&text1[count], &text2[count]);
        count++;
    }
}

int Mstrcmp(const char *str1, const char *str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    size_t pos = 0;
    while (str1[pos] != '\0' && str2[pos] != '\0') {
        char symbol1 = str1[pos];
        char symbol2 = str2[pos];

        if ('A' <= symbol1 && symbol1 <= 'Z') {
            symbol1 += 32;
        }
        if ('A' <= symbol2 && symbol2 <= 'Z') {
            symbol2 += 32;
        }

        if (symbol1 != symbol2) {
            return (symbol1 > symbol2) ? (1) : (-1);
        }
        pos++;
    }
    if (str1[pos] == '\0' && str2[pos] == '\0') {
        return 0;
    }

    return (str1[pos] == '\0') ? (-1) : (1);
}

void output_sorted_onegin(char *text[], size_t size) {
    assert(text != NULL);

    FILE *file = open_file("SortedOnegin.txt", "w");
    if (file == NULL) {
        perror("fopen() failed");
    }

    for (size_t i = 0; i < size; i++) {
        fprintf(file, "%s", text[i]);
    }

    PossibleErrors err = close_file(file);
    if (err != kNoError) {
        perror("fclose() failed");
    }
}

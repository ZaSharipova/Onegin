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

    char *tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
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
    assert(text != NULL);

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

    for (size_t pos = 0; pos < size; pos++) {
        fprintf(file, "%s\n", text[pos]);
    }

    PossibleErrors err = close_file(file);
    if (err != kNoError) {
        perror("fclose() failed");
    }
}

long long size_of_file(const char *filename) {
    assert(filename != NULL);

    struct stat stbuf;

    int err = stat(filename, &stbuf);
    if (err != kNoError) {
        perror("stat failed");
        return -1; //добавить ключ
    }

    return stbuf.st_size;
}

char *read_to_buf(const char *filename, FILE *file) {
    assert(filename != NULL);
    assert(file     != NULL);

    size_t filesize = (size_t)size_of_file(filename);

    char *buf = (char *) calloc(filesize + 1, sizeof(char));
    
    fread(buf, sizeof(buf[0]), filesize, file);

    return buf;
}

void parse_buf(char *buf, char **text_ptr) {
    assert(buf      != NULL);
    assert(text_ptr != NULL);

    size_t index_line = 0;
    //int cnt = 0;
    char *start = buf;
    while (index_line < FILESIZE && *start) {
        char *end = strchr(start, '\n');
        if (!end) {
            end = start + strlen(start);
        }
        
        size_t len = end - start;
        text_ptr[index_line] = (char *)calloc(len + 1, sizeof (char));

        memcpy(text_ptr[index_line], start, len);
        text_ptr[index_line][len] = '\0';
        index_line++;

        if (*end == '\n') {
            start = end + 1;
        } else {
            break;
        }
    }
}

PossibleErrors buf_input(const char *filename, char **text_ptr) {
    assert(filename != NULL);
    assert(text_ptr != NULL);

    FILE *file = open_file(filename, "r");
    if (file == NULL) {
        perror("fopen() failed");
        return kErrorOpening; //?
    }

    char *buf = read_to_buf(filename, file);
    assert(buf != NULL);

    parse_buf(buf, text_ptr);

    free(buf);

    int err = close_file(file);
    if (err != kNoError) {
        perror("fclse() failed");
        return kErrorClosing;
    }

    return kNoError;
}

void output_with_buf(char **text_ptr, FILE *file) {
    assert(text_ptr != NULL);
    assert(file     != NULL);

    size_t filesize = (size_t)size_of_file("textonegin.txt");
    char *buf = (char *) calloc(filesize + 5333, sizeof(char)); //размер подумать еще
    char *ptr = buf;
    for (size_t i = 0; i < FILESIZE; i++) { //
        size_t len = strlen(text_ptr[i]);

        memcpy(ptr, text_ptr[i], len);
        ptr += len;
        *ptr = '\n';
        ptr++;
    }
    *ptr = '\0';

    size_t size = strlen(buf);

    size_t status = fwrite(buf, sizeof(char), size, file);
    if (status != size) {
        perror("fwrite failed");
    }

    fclose(file);
    free(buf);
} 
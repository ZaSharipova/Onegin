#include "Sortings.h"
#include "ConstantsAndStructs.h"

#include <stdio.h>
#include <assert.h>
#include <ctype.h>

void swap_lineinfo(struct LineInfo *arr1, struct LineInfo *arr2) {
    assert(arr1 != NULL);
    assert(arr2 != NULL);

    struct LineInfo temp = *arr1;
    *arr1 = *arr2;
    *arr2 = temp;
}

int partition(struct LineInfo *text_ptr, int left, int right, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);

    int mid = (left + right) / 2;
    LineInfo pivot = text_ptr[mid];
    assert(mid < LINECOUNT);

    while (left <= right) {
        assert(left < LINECOUNT);
        assert(right >= 0);
        assert(right < LINECOUNT);
        
        while (left <= right && compares(&text_ptr[left], &pivot) < 0) {
            left++;
            assert(left < LINECOUNT);
        }

        while (left <= right && compares(&text_ptr[right], &pivot) > 0) {
            if (right <= 0) break;
            right--;
            assert(right >= 0);
        }

        if (left <= right) {
            swap_lineinfo(&text_ptr[left], &text_ptr[right]);
            left++;
            right--;
        }
    }

    return left;

}

void quick_sort(struct LineInfo *text_ptr, int left, int right, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);

    if (left + 1 >= right) {
        return;
    }

    assert(right - 1 < LINECOUNT);
    int sep = partition(text_ptr, left, right - 1, compares);
    quick_sort(text_ptr, left, sep, compares);
    quick_sort(text_ptr, sep, right, compares);
}

// void quick_sort_modified(char *text[], size_t left, size_t right, struct limits ) {
//     if (left + 1 >= right) {
//         return;
//     }

//     size_t sep = partition(text, left, right - 1);
    
//     quick_sort(text, left, sep);
//     quick_sort(text, sep, right);
// }

void bubble_sort(LineInfo *text_ptr, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);

    int sorted = 0;

    for (size_t i = 0; i < LINECOUNT - 1; i++) {
        for (size_t pos = 0; pos < LINECOUNT - i - 1; pos++) {
            if (compares(&text_ptr[pos], &text_ptr[pos + 1]) > 0) {
                swap_lineinfo(&text_ptr[pos], &text_ptr[pos + 1]);
                sorted = 1;
            }
        }

        if (sorted == 0) {
            break;
        }
    }
}

int Mstrcmp_ltor(char *start_ptr1, char *start_ptr2, char *end_ptr1, char *end_ptr2) {
    assert(start_ptr1 != NULL);
    assert(start_ptr2 != NULL);
    assert(end_ptr1   != NULL);
    assert(end_ptr2   != NULL);

    while (start_ptr1 <= end_ptr1 && start_ptr2 <= end_ptr2) {
        char symbol1 = (char)tolower(*start_ptr1);
        char symbol2 = (char)tolower(*start_ptr2);

        if (symbol1 != symbol2) {
            return (symbol1 > symbol2) ? (1) : (-1);
        }

        start_ptr1++, start_ptr2++;
    }

    if (start_ptr1 > end_ptr1 && start_ptr2 > end_ptr2) {
        return 0;
    }

    return ((start_ptr1 > end_ptr1) ? (-1) : (1));
}

int Mstrcmp_rtol(char *end_ptr1, char *end_ptr2, char *start_ptr1, char *start_ptr2) { //TODO подумать над названиями
    assert(end_ptr1   != NULL);
    assert(end_ptr2   != NULL);
    assert(start_ptr1 != NULL);
    assert(start_ptr2 != NULL);
    
    while (end_ptr1 >= start_ptr1 && end_ptr2 >= start_ptr2) {
        char symbol1 = (char)tolower(*end_ptr1);
        char symbol2 = (char)tolower(*end_ptr2);

        if (symbol1 != symbol2) {
            return (symbol1 > symbol2) ? (1) : (-1);
        }

        end_ptr1--, end_ptr2--;
    }

    if (end_ptr1 < start_ptr1 && end_ptr2 < start_ptr2) {
        return 0;
    }

    return (end_ptr1 < start_ptr1) ? (-1) : (1);
}

int compare_ltor(const void *text1, const void *text2) {
    assert(text1 != NULL);
    assert(text2 != NULL);
    
    const LineInfo *Arr1 = (const LineInfo *) text1;
    const LineInfo *Arr2 = (const LineInfo *) text2;

    return Mstrcmp_ltor(Arr1->start_ptr_alpha, Arr2->start_ptr_alpha, Arr1->end_ptr, Arr2->end_ptr);
}

int compare_rtol(const void *text1, const void *text2) {
    assert(text1 != NULL);
    assert(text2 != NULL);
    
    const LineInfo *Arr1 = (const LineInfo *) text1;
    const LineInfo *Arr2 = (const LineInfo *) text2;

    return Mstrcmp_rtol(Arr1->end_ptr_alpha, Arr2->end_ptr_alpha, Arr1->start_ptr, Arr2->start_ptr);
}
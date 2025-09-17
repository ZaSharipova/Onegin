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
    assert(left < LINECOUNT);
    return left;

}

void quick_sort(struct LineInfo *text_ptr, int left, int right, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);

    if (left + 1 >= right) {
        return;
    }

    assert(right - 1 < LINECOUNT);
    int sep = 0;
    if (right > 0) {
        sep = partition(text_ptr, left, right - 1, compares);
        quick_sort(text_ptr, left, sep, compares);
        quick_sort(text_ptr, sep, right, compares);
    }
}

// void quick_sort_modified(char *text[], size_t left, size_t right, struct limits ) {
//     if (left + 1 >= right) {
//         return;
//     }

//     size_t sep = partition(text, left, right - 1);
    
//     quick_sort(text, left, sep);
//     quick_sort(text, sep, right);
// }

void bubble_sort(LineInfo *text_ptr) {
    assert(text_ptr != NULL);

    int sorted = 0;
    for (size_t i = 0; i < 5331; i++) {
        for (size_t j = 0; j < 5331 - i; j++) {
            if (compare_RtoL(&text_ptr[j], &text_ptr[j + 1]) > 0) {
                swap_lineinfo(&text_ptr[j], &text_ptr[j + 1]);
                sorted = 1;
            }
        }
        if (sorted == 0) {
            break;
        }
    }
}

int Mstrcmp_LtoR(char *str1, char *str2, char *end_ptr1, char *end_ptr2) {
    assert(str1     != NULL);
    assert(str2     != NULL);
    assert(end_ptr1 != NULL);
    assert(end_ptr2 != NULL);

    while (str1 <= end_ptr1 && str2 <= end_ptr2) {
        char symbol1 = (char)tolower(*str1);
        char symbol2 = (char)tolower(*str2);

        if (symbol1 != symbol2) {
            return (symbol1 > symbol2) ? (1) : (-1);
        }

        str1++, str2++;
    }

    if (str1 > end_ptr1 && str2 > end_ptr2) {
        return 0;
    }

    return ((str1 > end_ptr1) ? (-1) : (1));
}

int Mstrcmp_RtoL(char *str1, char *str2, char *start_ptr1, char *start_ptr2) {
    assert(str1       != NULL);
    assert(str2       != NULL);
    assert(start_ptr1 != NULL);
    assert(start_ptr2 != NULL);
    
    while (str1 >= start_ptr1 && str2 >= start_ptr2) {
        char symbol1 = (char)tolower(*str1);
        char symbol2 = (char)tolower(*str2);

        if (symbol1 != symbol2) {
            return (symbol1 > symbol2) ? (1) : (-1);
        }

        str1--, str2--;
    }

    if (str1 < start_ptr1 && str2 < start_ptr2) {
        return 0;
    }

    return (str1 < start_ptr1) ? (-1) : (1);
}

int compare_LtoR(const void *a, const void *b) {
    assert(a != NULL);
    assert(b != NULL);
    
    const LineInfo *A = (const LineInfo *) a;
    const LineInfo *B = (const LineInfo *) b;

    return Mstrcmp_LtoR(A->start_ptr_alpha, B->start_ptr_alpha, A->end_ptr, B->end_ptr);
}

int compare_RtoL(const void *a, const void *b) {
    assert(a != NULL);
    assert(b != NULL);

    const LineInfo *A = (const LineInfo *) a;
    const LineInfo *B = (const LineInfo *) b;

    return Mstrcmp_RtoL(A->end_ptr_alpha, B->end_ptr_alpha, A->start_ptr, B->start_ptr);
}

int compare_bubble_LtoR(const void *a, const void *b) {
    assert(a != NULL);
    assert(b != NULL);

    const LineInfo *A = (const LineInfo *) a;
    const LineInfo *B = (const LineInfo *) b;

    return Mstrcmp_RtoL(A->start_ptr_alpha, B->start_ptr_alpha, A->end_ptr, B->end_ptr);
}
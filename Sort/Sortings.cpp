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

    int mid = rand_index(left, right);
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

    int dist = right - left;

    switch (dist) {
    case (0):
    case (1):
        return;

    case (2):
        compare_two_pointers(&text_ptr[left], &text_ptr[left + 1], compares);
        break;

    case (3):
        compare_three_pointers(text_ptr, left, right - 1, compares);
        break;

    case (4):
    case (5):
    case (6):
    case (7):
        insertion_sort(text_ptr, left, right, compares);
        break;

    default:
        assert(right - 1 < LINECOUNT);
        int sep = partition(text_ptr, left, right - 1, compares);
        quick_sort(text_ptr, left, sep, compares);
        quick_sort(text_ptr, sep, right, compares);
    }

    // if (size <= 1) {
    //     return;

    // } else {
    //     if (size == 2) {
    //         compare_two_pointers(&text_ptr[left], &text_ptr[left + 1], compares);
    //         return;
            
    //     } else {
    //         if (size == 3) {
    //             compare_three_pointers(text_ptr, left, right - 1, compares);
    //             return;

    //         } else {
    //             if (size >= 4 && size <= 7) {
    //                 insertion_sort(text_ptr, left, right, compares);
    //                 return;
    //             } 
    //         }
    //     }
    // } 

    // assert(right - 1 < LINECOUNT);
    // int sep = partition(text_ptr, left, right - 1, compares);
    // quick_sort(text_ptr, left, sep, compares);
    // quick_sort(text_ptr, sep, right, compares);
}

void quick_sort_with_stack(struct LineInfo *text_ptr, int line_count, int left_border, int right_border, int (*compares)(const void*, const void*)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);

    SortBorders *stack = (SortBorders *) calloc ((size_t)line_count, sizeof(SortBorders));
    assert(stack != NULL);
    
    int stack_size = line_count;
    int top = 0;

    stack[top].left = left_border;
    stack[top].right = right_border;

    while (top >= 0) {
        int left = stack[top].left;
        int right = stack[top].right;
        top--;

        int dist = right - left;

        if (dist <= 1) {
            continue;

        } else if (dist == 2) {
            compare_two_pointers(&text_ptr[left], &text_ptr[left + 1], compares);
            continue;

        } else if (dist == 3) {
            compare_three_pointers(text_ptr, left, right - 1, compares); //return ptr to func
            continue;

        } else if (4 <= dist && dist <= 7) {
            insertion_sort(text_ptr, left, right, compares);
            continue;
        }
        
        int sep = partition(text_ptr, left, right - 1, compares);

        if (sep > left) {
            top++;
            if (top > stack_size) {
                stack = (SortBorders *) realloc (stack, (size_t)stack_size + 1);
                assert(stack != NULL);

                stack_size++;
            }

            stack[top].left = left;
            stack[top].right = sep;
        }

        if (right > sep) {
            top++;
            stack[top].left = sep;
            stack[top].right = right;
        }
    }

    free(stack);
}

void bubble_sort(struct LineInfo *text_ptr, int line_count, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);

    int sorted = 0;

    for (int i = 0; i < line_count - 1; i++) {
        for (int pos = 0; pos < line_count - i - 1; pos++) {
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

void insertion_sort(struct LineInfo *text_ptr, int left, int right, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);
    
    for (int i = left + 1; i < right; i++) {
        LineInfo compared_str = text_ptr[i];
        int j = i - 1;

        while (j >= left && compares(&compared_str, &text_ptr[j]) < 0) {
            text_ptr[j + 1] = text_ptr[j];
            j--;
        }

        text_ptr[j + 1] = compared_str;
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

        start_ptr1++;
        start_ptr2++;
    }

    if (start_ptr1 > end_ptr1 && start_ptr2 > end_ptr2) {
        return 0;
    }

    return ((start_ptr1 > end_ptr1) ? (-1) : (1));
}

int Mstrcmp_rtol(char *end_ptr1, char *end_ptr2, char *start_ptr1, char *start_ptr2) {
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

void compare_two_pointers(struct LineInfo *str1, struct LineInfo *str2, int (*compare)(const void *, const void *)) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (compare(str1, str2) > 0) {
        swap_lineinfo(str1, str2);
    }
}

void compare_three_pointers(struct LineInfo *text_ptr, int left, int right, int (*compares)(const void *, const void *)) {
    assert(text_ptr != NULL);
    assert(compares != NULL);

    if (compares(&text_ptr[left], &text_ptr[left + 1]) > 0) {
        swap_lineinfo(&text_ptr[left], &text_ptr[left + 1]);
    }

    if (compares(&text_ptr[left + 1], &text_ptr[right]) > 0) {
        swap_lineinfo(&text_ptr[left + 1], &text_ptr[right]);

        if (compares(&text_ptr[left], &text_ptr[left + 1]) > 0) {
            swap_lineinfo(&text_ptr[left], &text_ptr[left + 1]);
        }
    }
}

int rand_index(int left, int right) {
    return left + (rand() % (right - left + 1));
}
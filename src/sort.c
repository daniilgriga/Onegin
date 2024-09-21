#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "sort.h"
#include "structs.h"
#include "compares.h"

void sort (void* addr, size_t n_rows, size_t el_size, compare_func_t compare_type)
{
    for (size_t i = 0; i < n_rows; i++)
    {
        for (size_t j = 0; j < n_rows - i - 1; j++)
        {
            void* elem_j  = (char*)addr   + j * el_size;
            void* elem_j1 = (char*)elem_j + 1 * el_size;

            if (compare_type(elem_j, elem_j1) > 0)
            {
                swap(elem_j, elem_j1, el_size);
            }
        }
    }
}

void swap (void* lhs, void* rhs, size_t el_size)
{
    char* lhs_bytes = lhs;
    char* rhs_bytes = rhs;

    for (size_t i = 0; i < el_size; i++) {
        char tmp = lhs_bytes[i];
                   lhs_bytes[i] = rhs_bytes[i];
                                  rhs_bytes[i] = tmp;
    }
}

#if 0
void my_qsort (void* addr, size_t n_rows, size_t el_size,  compare_func_t compare_type)
{
    if ((char*)addr < (char*)addr + n_rows * el_size)
    {
        size_t arr_part_i = seperation(addr, ..., n_rows, el_size, reverse_compare_str);

        my_qsort((char*)addr + ((n_rows - 1) / 2) * el_size, (n_rows - 1) / 2, el_size, compare_str);

        my_qsort((char*)addr + ((n_rows / 2) + 1) * el_size, (n_rows - 1) / 2, el_size, compare_str);
    }
}

size_t seperation (void* arr_i, size_t left, size_t right, size_t el_size,  compare_func_t compare_type)
{
    void* pivot = (char*)arr_i + right * el_size;
    size_t i = left - 1;

    for (size_t j = left; j < right; j++)
    {
        void* elem = (char*)arr_i + i * el_size;
        if (compare_type((char*)arr_i + i * el_size, pivot) > 0)
        {
            size_t k = ++i;
            swap((char*)arr_i + k * el_size, pivot, el_size);
        }
    }

    swap((char*)arr_i + (i + 1) * el_size, pivot, el_size);

    return (i + 1);
}
#endif


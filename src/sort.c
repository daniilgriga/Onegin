#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "sort.h"
#include "struct.h"


static size_t min_length(size_t lhs, size_t rhs) { return lhs > rhs ? rhs : lhs; }

int compare_str (void* str1, void* str2)
{
    return my_strcmp_forward(*(char**)str1, *(char**)str2);
}

int reverse_compare_str (void* str1, void* str2)
{
    return my_strcmp_reverse(*(char**)str1, *(char**)str2);
}

void sort (void* addr, size_t n_rows, size_t el_size, compare_func_t compare_type)
{
    for (size_t i = 0; i < n_rows; i++)
    {
        for (size_t j = 0; j < n_rows - i - 1; j++)
        {
            char** elem_j  = (char**)addr + j * el_size;
            char** elem_j1 = elem_j + 1;

            if (compare_type(elem_j, elem_j1) > 0)
            {
                swap(elem_j, elem_j1);
            }
        }
    }
}

void swap (char** lhs, char** rhs)
{
    char* tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}

int my_strcmp_forward(char* str1, char* str2)
{
    size_t n_byte = min_length(strlen(str1), strlen(str2));

    for (size_t i = 0; i < n_byte; i++)
    {

        if (!isalpha(*str1))
            ++str1;

        if (!isalpha(*str2))
            ++str2;

        if (tolower(*str1) == tolower(*str2))
        {
            ++str1;
            ++str2;
        }
    }

    return (tolower(*str1) - tolower(*str2));
}

int my_strcmp_reverse(char* str1, char* str2)
{
    size_t n_byte = min_length(strlen(str1), strlen(str2));

    size_t length_1 = strlen(str1);
    size_t length_2 = strlen(str2);

    for (size_t i = n_byte; i > 0; i--)
    {

        if (!isalpha(*(str1 + length_1)))
            --str1;

        if (!isalpha(*(str2 + length_2)))
            --str2;

        if (tolower(*(str1 + length_1)) == tolower(*(str2 + length_2)))
        {
            --str1;
            --str2;
        }
    }

    return (tolower(*(str1 + length_1)) - tolower(*(str2 + length_2)));
}



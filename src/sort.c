#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "sort.h"
#include "struct.h"

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

int my_strcmp_forward(char* str1, char* str2)
{

    for (; *str1 != '\0' && *str2 != '\0'; ++str1, ++str2)
    {

        while (*str1 != '\0' && !isalpha(*str1))
            ++str1;

        while (*str2 != '\0' && !isalpha(*str2))
            ++str2;

        if (tolower(*str1) != tolower(*str2) || *str1 == '\0')
        {
            break;
        }
    }

    return (tolower(*str1) - tolower(*str2));
}

int my_strcmp_reverse(char const* str1, char const* str2)
{
    ssize_t length_1 = (ssize_t)strlen(str1) - 1;
    ssize_t length_2 = (ssize_t)strlen(str2) - 1;

    for (; length_1 >= 0 && length_2 >= 0; --length_1, --length_2)
    {

        while (length_1 >= 0 && !isalpha(*(str1 + length_1)))
            --length_1;

        while (length_2 >= 0 && !isalpha(*(str2 + length_2)))
            --length_2;

        if (length_1 < 0 || length_2 < 0 || tolower(*(str1 + length_1)) != tolower(*(str2 + length_2)))
            break;
    }

    if (length_1 < 0 || length_2 < 0)
    {
        if (length_1 == length_2)
            return 0;
        else if (length_1 < 0)
            return -1;
        else
            return 1;
    }

    return (tolower(*(str1 + length_1)) - tolower(*(str2 + length_2)));
}



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "struct.h"
#include "compares.h"

int compare_str (const void* str1, const void* str2)
{
    return my_strcmp_forward(*(char**)str1, *(char**)str2);
}

int reverse_compare_str (const void* str1, const void* str2)
{
    return my_strcmp_reverse(*(char**)str1, *(char**)str2);
}

int compare_int (const void* int1, const void* int2)
{
    return (*(const int*)int1 - *(const int*)int2);
}

int my_strcmp_forward(const char* str1, const char* str2)
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

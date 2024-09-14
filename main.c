#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

#define LIGHT_BLUE  "\033[1;36m"
#define PURPLE      "\033[1;35m"
#define BLUE        "\033[1;34m"
#define GREEN       "\033[1;32m"
#define CLEAR_COLOR "\033[0m"

#define LIGHT_BLUE_TEXT(text) LIGHT_BLUE text CLEAR_COLOR
#define PURPLE_TEXT(text)     PURPLE text CLEAR_COLOR
#define BLUE_TEXT(text)       BLUE text CLEAR_COLOR
#define GREEN_TEXT(text)      GREEN text CLEAR_COLOR

void swap(void* addr_str1, void* addr_str2, size_t num);

int compare_str (void* str1, void* str2);
typedef int (*compare_func_t)(void* str1, void* str2);

void sort (void* buffer, size_t n_rows, size_t el_size, compare_func_t compare_char);

int main (void)
{
    FILE * onegin = fopen( "onegin.txt", "r");
    assert(onegin && "File reading error");

    fseek(onegin, 0, SEEK_END);
    long file_size = ftell(onegin);
    rewind(onegin);

    char* buffer = (char*) calloc((size_t)file_size + 1, sizeof(char));
    if (buffer == NULL)
        printf("Storage error");

    size_t read_result = fread(buffer, 1, (size_t)file_size, onegin);
    assert((read_result == (size_t)file_size) && "Read error");

    printf("%s", buffer);

    size_t count_rows = 0;
    for(int i = 0; i < file_size; i++)
    {
        if (buffer[i] == '\n')
            count_rows++;
    }
    printf("\n%zu\n\n", count_rows);

    char** addr_strings = (char**) calloc((size_t)count_rows + 1, sizeof(char*));
    addr_strings[0] = buffer;

    int j = 0;
    for(int i = 0; i < file_size; i++)
    {
        if(buffer[i] == '\n')
        {
            char* addr_n = &buffer[i];
            addr_strings[j + 1] = addr_n + 1;
            *addr_n = '\0'; // clean '\n'

            if (*(addr_n - 1) == '\r')
                *(addr_n - 1) = '\0'; // clean '\r'
            j++;
        }
    }

    sort (addr_strings, count_rows, sizeof(char*), compare_str);

    putchar('\n');

    for (size_t i = 0; i < count_rows; i++)
        printf("%s\n", addr_strings[i]);

    putchar('\n');

    fclose(onegin);
    free(buffer);
    free(addr_strings);

    return 0;
}

void sort (void* addr_str, size_t n_rows, size_t el_size, compare_func_t compare_type)
{
    for (size_t i = 0; i < n_rows; i++)
    {
        for (size_t j = 0; j < n_rows - i - 1; j++)
        {
            void* elem_j  = (char*)addr_str + j * el_size;
            void* elem_j1 = (char*)addr_str + (j + 1) * el_size;

            printf(""PURPLE_TEXT("before compare: ")"addr_elem_j  = %p\n", elem_j);
            printf(""PURPLE_TEXT("before compare: ")"addr_elem_j1 = %p\n", elem_j1);

            printf(""PURPLE_TEXT("before compare: ")"elem_j  = <%s>\n", *(char**)elem_j);
            printf(""PURPLE_TEXT("before compare: ")"elem_j1 = <%s>\n", *(char**)elem_j1);

            if (compare_type(elem_j, elem_j1) > 0) // *(char**)n = (char*)n
            {
                printf(""BLUE_TEXT("before swap: ")"i = %zu: str[j]   = <%s>\n"
                       "\t\t    str[j+1] = <%s>  \n", i, *(char**)elem_j, *(char**)elem_j1);

                printf(""BLUE_TEXT("before swap: ")"elem_j  = %p\n", elem_j);
                printf(""BLUE_TEXT("before swap: ")"elem_j1 = %p\n", elem_j1);

                swap(elem_j, elem_j1, sizeof(elem_j1));

                printf(""BLUE_TEXT("after swap: ")" i = %zu: str[j]  = <%s>\n"
                       "\t\t    str[j+1] = %s\n\n", i, *(char**)elem_j, *(char**)elem_j1);

                printf(""BLUE_TEXT("after swap: ")"elem_j  = %p\n", elem_j);
                printf(""BLUE_TEXT("after swap: ")"elem_j1 = %p\n", elem_j1);
            }

            printf("\n-----------------------new iteration(i = %zu, j = %zu)-----------------------\n\n", i, j);
        }

        printf("\n-----------------------new iteration(i = %zu)-----------------------\n\n", i);
    }
}

void swap(void* str1, void* str2, size_t num)
{
    printf("\n"LIGHT_BLUE_TEXT("swapping")"\n\n");
    for (size_t i = 0; i < num; i++)
    {
        char c = ((char*)str1)[i];
                 ((char*)str1)[i] = ((char*)str2)[i];
                                    ((char*)str2)[i] = c;
    }
}

int compare_str (void* str1, void* str2)
{
    putchar('\n');
    printf(""GREEN_TEXT("in compare_char: ")"addr_elem_j  = %p\n"
           "\t\t addr_elem_j1 = %p\n", (char*)str1, ((char*)str2));
    printf(""GREEN_TEXT("in compare_char: ")"elem_j  = %p\n", str1);
    printf(""GREEN_TEXT("in compare_char: ")"elem_j1 = %p\n\n", str2);

    return strcmp(*(char**)str1, *(char**)str2);
}

// 1 func without punctuation and spaces
//
// ! struct addr string and length string
// i am not a fool, i am debug king
// i'll take you on the ring
// you'll get your ping
// ! reversed compared

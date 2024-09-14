#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

void swap(void* addr_str1, void* addr_str2, size_t num);

//void swap_ch (char str1[], char str2[], size_t n_colls);

int compare_char (void* str1, void* str2);
typedef int (*compare_func_t)(void* str1, void* str2);

void sort (void* buffer, size_t n_rows, size_t el_size, compare_func_t compare_char);

//void my_sort (char* array, size_t file_size , size_t size, compare_func_t compare_char);

int main (void)
{
    FILE * onegin = fopen( "onegin.txt", "r");
    assert(onegin && "File reading error");

    fseek(onegin, 0, SEEK_END);
    long file_size = ftell(onegin);
    rewind(onegin);

    char* buffer = (char*) calloc((size_t)file_size + 1, sizeof(char));
    assert(buffer && "Storage error");

    size_t read_result = fread(buffer, 1, (size_t)file_size, onegin);
    assert((read_result == (size_t)file_size) && "Read error");

    printf("%s", buffer);

    size_t count_rows = 0;
    for(int i = 0; i < file_size; i++)
    {
        if (buffer[i] == '\n')
        {
            count_rows++;
        }
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
            *(addr_n - 1) = '\0'; // clean '\r'
            *addr_n = '\0'; // clean '\n'

            j++;
        }
    }

    sort (addr_strings, count_rows, sizeof(char*), compare_char);
    // sort (buffer, count_rows, sizeof(char*), compare_char);

    putchar('\n');

    for (size_t i = 0; i < count_rows; i++)
        printf("%s\n", addr_strings[i]);

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
            printf("addr_elem_j  = %p\n", elem_j);
            printf("addr_elem_j1 = %p\n", elem_j1);

            printf("\nelem_j  = <%s>\n", *(char**)elem_j);
            printf("\nelem_j1 = <%s>\n", *(char**)elem_j1);

            printf("addr_rand[%zu] = %p, addr_rand[%zu] = %p\n", j, elem_j, j + 1, elem_j1);

            if (compare_type(elem_j, elem_j1) > 0) // *(char**)n = (char*)n
            {
                printf("before swap: i = %zu: str[j] = %s vs str[j+1] = %s  \n",
                       i, *(char**)elem_j, *(char**)elem_j1);

                printf("before swap: elem_j  = %p\n", elem_j);
                printf("before swap: elem_j1 = %p\n", elem_j1);

                swap(elem_j, elem_j1, sizeof(elem_j1));

                printf("after swap:  i = %zu: str[j] = %s vs str[j+1] = %s\n\n",
                       i, *(char**)elem_j, *(char**)elem_j1);

                printf("after swap: elem_j  = %p\n", elem_j);
                printf("after swap: elem_j1 = %p\n", elem_j1);
            }
        }
    }
}

void swap(void* str1, void* str2, size_t num)
{
    printf("\nswapping\n");
    for (size_t i = 0; i < num; i++)
    {
        char c = ((char*)str1)[i];
                 ((char*)str1)[i] = ((char*)str2)[i];
                                    ((char*)str2)[i] = c;
    }
}

int compare_char (void* str1, void* str2)
{
    printf("\nin compare_char: addr_rand[0] = %p, addr_rand[1] = %p\n", (char*)str1, ((char*)str2));
    printf("in compare_char: elem_j  = %p\n", str1);
    printf("in compare_char: elem_j1 = %p\n\n", str2);

    return strcmp(*(char**)str1, *(char**)str2);
    // printf
}

// func without punctuation and spaces
//
// struct addr string and length string
// i am not a fool, i am debug king
// i'll take you on the ring
// you'll get your ping
// reversed compared

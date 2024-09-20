#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

enum array {N_ROWS = 14, N_COLLS = 52};

void replacement_n(char* text);

void swap (char* str1, char* str2);

void swap2 (char str1[], char str2[], int n_colls);

void swap3 (char str1[], char str2[], int n_colls);

int main (void)
{
    /*char str1[] = "ded here123";
    char str2[] = "DAN REAL789";


    printf("str1 = <%s>\n", str1);
    printf("str2 = <%s>\n", str2);

    //replacement_n(str1);
    //replacement_n(str2);

    swap3(str1, str2, 11);
c
    printf("str1 = <%s>\n", str1);
    printf("str2 = <%s>\n", str2);*/



    FILE* onegin = fopen("onegin.txt", "r");

    assert(onegin && "File reading error");

    char text[N_ROWS][N_COLLS] = {};

    for (int i = 0; i < N_ROWS; i++)
        fgets(text[i], 50, onegin);

    for (int i = 0; i < N_ROWS; i++)
        replacement_n(text[i]);

    for (int i = 0; i < N_ROWS; i++)
    {
        printf("text[%d] = (%s)", i, text[i]);
        putchar('\n');
    }

    putchar('\n');

    for (int i = 0; i < N_ROWS; i++)
    {
        for (int j = 0; j < N_ROWS - i - 1; j++)
        {
            int strcmp_result = strcmp(text[j], text[j+1]);

            if (strcmp_result > 0)
                swap3(text[j], text[j + 1], N_COLLS); // also can use swap!
        }
    }

    for (int i = 0; i < N_ROWS; i++)
    {
        printf("text[%d] = <%s>", i, text[i]);
        putchar('\n');
    }

    putchar('\n');

    fclose(onegin);
    return 0;
}

static size_t max(size_t lhs, size_t rhs) { return lhs < rhs ? rhs : lhs; }

void swap (char* str1, char* str2)
{
    char* change = (char*)calloc(max(strlen(str1), strlen(str2)) + 1, sizeof(char));

    strcpy(change, str1);
    strcpy(str1  , str2);
    strcpy(str2  , change);

    free(change);
}

void swap2 (char str1[], char str2[], int n_colls) // better!
{
    for (int i = 0; i < n_colls; i++)
    {
        char c = str1[i];
                 str1[i] = str2[i];
                           str2[i] = c;
    }

}

void swap3 (char str1[], char str2[], int n_colls)
{
    int i = 0;

    for (i; i < n_colls/4; i++)
    {
        int c  = *(int*)(str1 + 4 * i);
        int c2 = *(int*)(str1 + 4 * i) = *(int*)(str2 + 4 * i);
                                         *(int*)(str2 + 4 * i) = c;
    }

    for (int j = i * 4; j < n_colls % 4; j++)
    {
         char c = str1[j];
                  str1[j] = str2[j];
                            str2[j] = c;
    }
}


void replacement_n(char* str)
{
    if (strcspn(str, "\r\n") != 0)
        str[strcspn(str, "\r\n")] = 0;
}
void sort (char** addr_str, size_t n_rows, compare_func_t compare_char)
{
    for (size_t i = 0; i < n_rows; i++)
    {
        for (size_t j = 0; j < n_rows - i - 1; j++)
        {
            if (strcmp(addr_str[j], addr_str[j + 1]) > 0)
            {
                printf("swap:       i = %zu: str[j] = %s vs str[j+1] = %s  \n", i, addr_str[j], addr_str[j + 1]);

                swap(&(addr_str[j]), &(addr_str[j + 1]));

                printf("after swap: i = %zu: str[j] = %s vs str[j+1] = %s\n\n", i, addr_str[j], addr_str[j + 1]);
            }
        }
    }
}

void sort (void** addr_strings, size_t n_rows, size_t el_size, compare_func_t compare_type)
{
    for (size_t i = 0; i < n_rows; i++)
    {
        for (size_t j = 0; j < n_rows - i - 1; j++)
        {
            if (compare_type(addr_strings + j * el_size, addr_strings + (j + 1) * el_size) > 0)
            {
                printf("swap:       i = %zu: str[j] = %s vs str[j+1] = %s  \n", i, addr_strings + j * el_size, addr_strings + (j + 1) * el_size);

                swap(&(addr_strings + j * el_size), &(addr_strings + (j + 1) * el_size));

                printf("after swap: i = %zu: str[j] = %s vs str[j+1] = %s\n\n", i, addr_strings + j * el_size, addr_strings + (j + 1) * el_size);
            }
        }
    }
}

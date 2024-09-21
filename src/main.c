#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

#include "structs.h"
#include "color_print.h"
#include "compares.h"
#include "file_data.h"
#include "qsort_exmpls.h"
#include "sort.h"

const char* HELP_FLAG = "--help";

void create_array_of_pointers (struct file_data* onegin);

struct file_data read_file_func (const char* file_read);

int main (const int argc, const char* argv[])
{
    if (argc == 2 && strcmp(argv[1], HELP_FLAG) == 0)
    {
        printf("This program will give you wings. It simply sorts a set of strings :D\n");
        return 0;
    }

    if (argc >= 2 && strcmp(argv[1], HELP_FLAG))
    {
        printf("Error. This unknown flags, you can use only \"%s\"!!!\n", HELP_FLAG);
        return 1;
    }

    struct file_data onegin = read_file_func("onegin.txt");

    struct data_str* strings = (struct data_str*)calloc(onegin.count_rows, sizeof(struct data_str));

    for (size_t i = 0; i < onegin.count_rows; i++)
    {
        strings[i].str = onegin.addr_strings[i];
        strings[i].length_str = strlen(onegin.addr_strings[i]);
        printf("%s  %zu\n",  strings[i].str, strings[i].length_str);
    }
    printf("\n");

    sort (strings, onegin.count_rows, sizeof(strings[0]), reverse_compare_str);

    // printf("\n"PURPLE_TEXT("the sorqted contents of the file:"));
    for (size_t i = 0; i < onegin.count_rows; i++)
        printf("%s\n", strings[i].str);
    // printf("\n"PURPLE_TEXT("the end of the sorted file.")"\n\n");

    #if 0
    example_use_qsort_int();
    example_use_qsort_str(&onegin);
    #endif

    free(strings);
    free(onegin.buffer);
    free(onegin.addr_strings);

    return 0;
}

struct file_data read_file_func (const char* file_read)
{
    struct file_data onegin = {};

    if (file_reader(&onegin, file_read) == 1)
    {
        printf("System message 99173: PIZDEC occurred\n");
    }

    // printf("\n"BLUE_TEXT("the contents of the file:")"\n\n");
    printf("%s\n", onegin.buffer);
    // printf(BLUE_TEXT("the end of the file.")"\n");

    onegin.count_rows = count_rows(&onegin);

    create_array_of_pointers(&onegin);

    return onegin;
}

void create_array_of_pointers (struct file_data* onegin)
{
    onegin->addr_strings = (char**) calloc(onegin->count_rows + 1, sizeof(char*));
    onegin->addr_strings[0] = onegin->buffer;

    int j = 0;
    for(long i = 0; i < onegin->file_size; i++)
    {
        if(onegin->buffer[i] == '\n') // ANCHOR
        {
            char* addr_n = &onegin->buffer[i];

            onegin->addr_strings[j + 1] = addr_n + 1;

            *addr_n = '\0'; // clean '\n'

            if (addr_n > &onegin->buffer[0] && *(addr_n - 1) == '\r')
                *(addr_n - 1) = '\0'; // clean '\r'
            j++;
        }
    }
}

// struct addr string and length string
// i am not a fool, i am debug king
// i'll take you on the ring
// you'll get your ping

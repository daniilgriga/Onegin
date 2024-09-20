#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

#include "struct.h"
#include "color_print.h"
#include "compares.h"
#include "file_data.h"
#include "qsort_exmpls.h"
#include "sort.h"

#define QSORT
const char* HELP_FLAG = "--help";

void create_array_of_pointers (struct data_t* onegin);

int main (const int argc, const char* argv[]) // ANCHOR
{
    if (argc == 2 && strcmp(argv[1], HELP_FLAG) == 0)
    {
        printf("This program sorts the strings :D\n");
        return 0;
    }

    if (argc >= 2 && strcmp(argv[1], HELP_FLAG))
    {
        printf("Error. This unknown flags, you can use only \"%s\"!!!\n", HELP_FLAG);
        return 1;
    }

    struct data_t onegin = {};

    if(file_reader (&onegin) == 1)
    {
        printf("pizdec");
        return 1;
    }

    // printf("\n"BLUE_TEXT("the contents of the file:")"\n\n");
    printf("%s\n", onegin.buffer);
    // printf(BLUE_TEXT("the end of the file.")"\n");

    onegin.count_rows = count_rows(&onegin);

    create_array_of_pointers(&onegin);

    sort (onegin.addr_strings, onegin.count_rows, sizeof(char*), reverse_compare_str);

    // printf("\n"PURPLE_TEXT("the sorted contents of the file:"));
    for (size_t i = 0; i < onegin.count_rows; i++)
        printf("%s\n", onegin.addr_strings[i]);
    // printf("\n"PURPLE_TEXT("the end of the sorted file.")"\n\n");

    // example_use_qsort_int();
    // example_use_qsort_str(&onegin);

    free(onegin.buffer);
    free(onegin.addr_strings);

    return 0;
}

void create_array_of_pointers (struct data_t* onegin)
{
    onegin->addr_strings = (char**) calloc(onegin->count_rows + 1, sizeof(char*));
    onegin->addr_strings[0] = onegin->buffer; // ANCHOR

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

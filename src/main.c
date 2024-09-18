#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

#include "struct.h"
#include "file_stat.h"
#include "sort.h"


// #define LIGHT_BLUE  "\033[1;36m"
// #define PURPLE      "\033[1;35m"
// #define BLUE        "\033[1;34m"
// #define GREEN       "\033[1;32m"
// #define CLEAR_COLOR "\033[0m"
//
// #define LIGHT_BLUE_TEXT(text) LIGHT_BLUE text CLEAR_COLOR
// #define PURPLE_TEXT(text)     PURPLE text CLEAR_COLOR
// #define BLUE_TEXT(text)       BLUE text CLEAR_COLOR
// #define GREEN_TEXT(text)      GREEN text CLEAR_COLOR

void create_array_of_pointers (struct data_t* onegin);

int main (void)
{
    struct data_t onegin = {};

    if(file_reader (&onegin) == 1) {
        printf("pizda");
        return 1;
    }

    printf("%s\n", onegin.buffer);

    onegin.count_rows = count_rows(onegin);

    create_array_of_pointers(&onegin);

    sort (onegin.addr_strings, onegin.count_rows, sizeof(char*), reverse_compare_str);

    for (size_t i = 0; i < onegin.count_rows; i++)
        printf("%s\n", onegin.addr_strings[i]);

    free(onegin.buffer);
    free(onegin.addr_strings);

    return 0;
}


// struct addr string and length string
// i am not a fool, i am debug king
// i'll take you on the ring
// you'll get your ping

void create_array_of_pointers (struct data_t* onegin)
{
    onegin->addr_strings = (char**) calloc((size_t)onegin->count_rows + 1, sizeof(char*));
    onegin->addr_strings[0] = onegin->buffer;

    int j = 0;
    for(int i = 0; i < onegin->file_size; i++)
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


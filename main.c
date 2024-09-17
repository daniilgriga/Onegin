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

struct data_t
{
    char*  buffer;
    long   file_size;
    char** addr_strings;
    size_t count_rows;
};

int file_reader (struct data_t* file);

void count_symbols (struct data_t* onegin, FILE* file);

size_t count_rows (struct data_t onegin);

void array_of_pointers (struct data_t* onegin);

int my_strcmp(char* str1, char* str2);

// void swap(void* addr_str1, void* addr_str2, size_t num);
void swap (char **lhs, char **rhs);
int compare_str (void* str1, void* str2);

typedef int (*compare_func_t)(void* str1, void* str2);
void sort (void* addr, size_t n_rows, size_t el_size, compare_func_t compare_char);

int main (void)
{
    struct data_t onegin = {};

    if(file_reader (&onegin) == 1)
        printf("pizda");

    printf("%s\n", onegin.buffer);

    onegin.count_rows = count_rows(onegin);

    array_of_pointers(&onegin);

    sort (onegin.addr_strings, onegin.count_rows, sizeof(char), compare_str);

    for (size_t i = 0; i < onegin.count_rows; i++)
        printf("%s\n", onegin.addr_strings[i]);

    free(onegin.buffer);
    free(onegin.addr_strings);

    return 0;
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

void swap(char** lhs, char** rhs)
{
    char* tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}

int compare_str (void* str1, void* str2)
{
    return my_strcmp(*(char**)str1, *(char**)str2);
}

// 1 func without punctuation and spaces +
//
// ! struct addr string and length string
// i am not a fool, i am debug king
// i'll take you on the ring
// you'll get your ping
// ! reversed compared

int file_reader (struct data_t* onegin)
{
    FILE* file = fopen("onegin.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Open error");
        return 1;
    }

    count_symbols (onegin, file);

    onegin->buffer = (char*) calloc((size_t)(onegin->file_size) + 1, sizeof(char));
    if (onegin->buffer == NULL)
    {
        fprintf(stderr, "Storage error");
        return 1;
    }

    size_t read_result = fread(onegin->buffer, 1, (size_t)onegin->file_size, file);
    if (read_result != (size_t)onegin->file_size)
    {
        fprintf(stderr, "Read error");
        return 1;
    }

    fclose(file);

    return 0;
}

void count_symbols (struct data_t* onegin, FILE* file)
{
    fseek(file, 0, SEEK_END);
    onegin->file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
}

size_t count_rows (struct data_t onegin)
{
    onegin.count_rows = 0;
    for(int i = 0; i < onegin.file_size; i++)
    {
        if (onegin.buffer[i] == '\n')
            onegin.count_rows++;
    }

    return onegin.count_rows;
}


void array_of_pointers (struct data_t* onegin)
{
    onegin->addr_strings = (char**) calloc((size_t)onegin->count_rows + 1, sizeof(char*));
    onegin->addr_strings[0] = onegin->buffer;

    int j = 0;
    for(int i = 0; i < onegin->file_size; i++)
    {
        if(onegin->buffer[i] == '\n')
        {
            char* addr_n = &onegin->buffer[i];

            onegin->addr_strings[j + 1] = addr_n + 1;

            *addr_n = '\0'; // clean '\n'

            if (*(addr_n - 1) == '\r')
                *(addr_n - 1) = '\0'; // clean '\r'
            j++;
        }
    }
}


static size_t min_length(size_t lhs, size_t rhs) { return lhs > rhs ? rhs : lhs; }

int my_strcmp(char* str1, char* str2)
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

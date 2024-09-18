#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "struct.h"
#include "file_stat.h"

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

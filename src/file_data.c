#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "structs.h"
#include "file_data.h"

int file_reader (struct file_data* onegin, const char* file_read)
{
    assert(onegin);

    FILE* file = fopen(file_read, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Open error");
        return 1;
    }

    if (count_symbols(onegin, file) == -1)
        return 1;

    onegin->buffer = (char*) calloc((size_t)(onegin->file_size) + 1, sizeof(char));
    if (onegin->buffer == NULL)
    {
        fprintf(stderr, "Storage error");
        return 1;
    }

    size_t read_result = fread(onegin->buffer, sizeof(char), (size_t)onegin->file_size, file);
    if (read_result != (size_t)onegin->file_size)
    {
        fprintf(stderr, "Read error");
        return 1;
    }

    fclose(file);

    return 0;
}

int count_symbols (struct file_data* onegin, FILE* file)
{
    if (fseek(file, 0, SEEK_END) != 0)
        return -1;

    onegin->file_size = ftell(file); // FIXME cast to size_t
    if (onegin->file_size == -1)
        return -1;

    if (fseek(file, 0, SEEK_SET) != 0)
        return -1;

    return 0;
}

size_t count_rows (struct file_data* onegin)
{
    onegin->count_rows = 0;

    for(int i = 0; i < onegin->file_size; i++)
    {
        if (onegin->buffer[i] == '\n')
            onegin->count_rows++;
    }

    return onegin->count_rows;
}

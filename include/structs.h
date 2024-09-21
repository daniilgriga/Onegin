#ifndef STRUCT_H_
#define STRUCT_H_

struct file_data
{
    char*  buffer;
    long   file_size;
    char** addr_strings;
    size_t count_rows;
};

struct data_str
{
    char* str;
    size_t length_str;
};

#endif // STRUCT_H

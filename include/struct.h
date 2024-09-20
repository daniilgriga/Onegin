#ifndef STRUCT_H_
#define STRUCT_H_

struct data_t
{
    char*  buffer;
    long   file_size;
    char** addr_strings;
    size_t count_rows;
};

#endif // STRUCT_H

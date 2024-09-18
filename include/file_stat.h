#ifndef FILE_STAT_H_
#define FILE_STAT_H_

int file_reader (struct data_t* onegin);

int count_symbols (struct data_t* onegin, FILE* file);

size_t count_rows (struct data_t onegin);

#endif

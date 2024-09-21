#ifndef FILE_STAT_H_
#define FILE_STAT_H_

int file_reader (struct file_data* onegin, const char* file_read);

int count_symbols (struct file_data* onegin, FILE* file);

size_t count_rows (struct file_data* onegin);

#endif // FILE_STAT_H

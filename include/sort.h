#ifndef SORT_H_
#define SORT_H_

int compare_str (void* str1, void* str2);
typedef int (*compare_func_t)(void* str1, void* str2);

int reverse_compare_str (void* str1, void* str2);

void sort (void* addr, size_t n_rows, size_t el_size, compare_func_t compare_char);

void swap (char **lhs, char **rhs);

int my_strcmp_forward(char* str1, char* str2);

int my_strcmp_reverse(char* str1, char* str2);

#endif

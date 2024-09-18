#ifndef SORT_H_
#define SORT_H_

int compare_str (void* str1, void* str2);
typedef int (*compare_func_t)(void* str1, void* str2);

int reverse_compare_str (void* str1, void* str2);

void sort (void* addr, size_t n_rows, size_t el_size, compare_func_t compare_char);

void swap (void *lhs, void *rhs, size_t el_size);

int my_strcmp_forward(char* str1, char* str2);

int my_strcmp_reverse(char const* str1, char const* str2);

#endif

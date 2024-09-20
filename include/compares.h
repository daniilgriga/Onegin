#ifndef COMPARES_H_
#define COMPARES_H_

int compare_str (const void* str1, const void* str2);
typedef int (*compare_func_t)(const void* str1, const void* str2);

int reverse_compare_str (const void* str1, const void* str2);

int compare_int (const void* int1, const void* int2);

int my_strcmp_forward(const char* str1, const char* str2);

int my_strcmp_reverse(char const* str1, char const* str2);

#endif // COMPARES_H_

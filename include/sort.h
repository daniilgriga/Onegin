#ifndef SORT_H_
#define SORT_H_

typedef int (*compare_func_t)(const void* str1, const void* str2);
void sort (void* addr, size_t n_rows, size_t el_size,  compare_func_t compare_type);

#if 0
void my_qsort (void* addr, size_t n_rows, size_t el_size,  compare_func_t compare_type);

size_t seperation (void* arr_i, size_t left, size_t right, size_t el_size,  compare_func_t compare_type);
#endif

void swap (void *lhs, void *rhs, size_t el_size);


#endif // SORT_H_

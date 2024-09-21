#include <stdio.h>

#include "structs.h"
#include "qsort_exmpls.h"
#include "sort.h"
#include "color_print.h"
#include "compares.h"

void example_use_qsort_int (void) // -------------------------------- qsort for int type
{
    printf(LIGHT_BLUE_TEXT("\nqsort for int usage example:")"\n\n");

    int arr_i[] = {5, 2, 6, 3, 4, 9, 9, 2, 8, 6};

    for (int i = 0; i < 10; i++)
        printf("%d  ", arr_i[i]);

    puts("\n");
    qsort(arr_i, 10, sizeof(int), compare_int);

    for (int i = 0; i < 10; i++)
        printf("%d  ", arr_i[i]);

    puts("\n\n");
}

void example_use_qsort_str (struct file_data* onegin) // --------------- qsort for str type
{
    printf(GREEN_TEXT("qsort for string usage example (onegin.txt):")"\n\n");

    qsort(onegin->addr_strings, onegin->count_rows, sizeof(char*), reverse_compare_str);

    for (size_t i = 0; i < onegin->count_rows; i++)
        printf("%s\n", onegin->addr_strings[i]);
}

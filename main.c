#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

enum array {N_ROWS = 14, N_COLLS = 50};

void swap (char* str1, char* str2);

int main (void)
{
    FILE* onegin = fopen("onegin.txt", "r");

    assert(onegin && "File reading error");

    char text[N_ROWS][N_COLLS] = {};

    for (int i = 0; i < N_ROWS; i++)
        fgets(text[i], 50, onegin);

    for (int i = 0; i < N_ROWS; i++)
    {
        printf("text[%d] = %s", i, text[i]);
        putchar('\n');
    }

    putchar('\n');

    for (int i = 0; i < N_ROWS; i++)
    {
        for (int j = 0; j < N_ROWS - i - 1; j++)
        {
            int strcmp_result = strcmp(text[j], text[j+1]);

            if (strcmp_result > 0)
                swap(text[j], text[j + 1]);
        }
    }

    for (int i = 0; i < N_ROWS; i++)
    {
        printf("text[%d] = %s", i, text[i]);
        putchar('\n');
    }

    return 0;
}

static size_t max(size_t lhs, size_t rhs) { return lhs < rhs ? rhs : lhs; }

void swap (char* str1, char* str2)
{
    char* change = (char*)calloc(max(strlen(str1), strlen(str2)) + 1, sizeof(char));

    strcpy(change, str1);
    strcpy(str1  , str2);
    strcpy(str2  , change);

    free(change);
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

#define N_ROWS 15
#define N_COLLS 50

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

    printf("start");

    for (int i = 0; i < N_ROWS; i++)
    {
        printf("start swapping1");
        for (int j = 0; j < N_ROWS - i - 1; j++)
        {
            int strcmp_result = strcmp(text[j], text[j+1]);
            printf("start swapping2");
            if (strcmp_result > 0)
                swap(text[j], text[j]);
        }
    }

    for (int i = 0; i < N_ROWS; i++)
    {
        printf("text[%d] = %s", i, text[i]);
        putchar('\n');
    }

    return 0;
}

void swap (char* str1, char* str2)
{
    char* change = (char*)calloc((strlen(str1) + 1), sizeof(char));

    strcpy(change, str1);
    strcpy(str1  , str2);
    strcpy(str2  , change);

    free(change);
}

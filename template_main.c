#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 100

typedef struct
{
    size_t *index;
    size_t capacity;
    int *arr;
} DA;

void da_append(DA *list, int value)
{
    if (*(list->index) >= list->capacity)
    {
        list->capacity += N;
        list->arr = realloc(list->arr, list->capacity * sizeof(int));
    }
    list->arr[*(list->index)] = value;
    *(list->index) += 1;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Use : ./main part1|part2|all\n");
        return 1;
    }

    char *parte = argv[1];
    FILE *f = fopen("input.txt", "r");

    DA *list = malloc(sizeof(*list));

    list->arr = malloc(N * sizeof(int));
    size_t index = 0;
    list->index = &index;
    list->capacity = N;

    if (strcmp(parte, "parte1") == 0 || strcmp(parte, "all") == 0)
    {
        char *line = NULL;
        size_t len = 0;

        while (getline(&line, &len, f) != EOF)
        {
        }
        free(line);
        // printf("result parte 1 = %d\n", count_safe);
    }

    if (strcmp(parte, "parte2") == 0 || strcmp(parte, "all") == 0)
    {
        char *line = NULL;
        size_t len = 0;

        while (getline(&line, &len, f) != EOF)
        {
        }
        free(line);
        // printf("result parte 2 = %d\n", count_safe);
    }

    fclose(f);
    free(list->arr);
    return 0;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct
{
    size_t index;
    size_t capacity;
    int *arr;
} DA;

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void da_append(DA *list, int value)
{
    if (list->index >= list->capacity)
    {
        list->capacity += N;
        list->arr = realloc(list->arr, list->capacity * sizeof(int));
    }

    list->arr[list->index] = value;
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

    DA list1;
    DA list2;

    list1.arr = malloc(N * sizeof(int));
    list2.arr = malloc(N * sizeof(int));
    list1.index = 0;
    list2.index = 0;
    list1.capacity = N;
    list2.capacity = N;

    int tmp1 = 0;
    int tmp2 = 0;
    while (fscanf(f, "%d   %d\n", &tmp1, &tmp2) != EOF)
    {
        da_append(&list1, tmp1);
        da_append(&list2, tmp2);
        list1.index += 1;
        list2.index += 1;
    }

    if (strcmp(parte, "parte1") == 0 || strcmp(parte, "all") == 0)
    {
        qsort(list1.arr, list1.index, sizeof(int), compare);
        qsort(list2.arr, list2.index, sizeof(int), compare);

        int res = 0;
        for (size_t i = 0; i < list1.index; ++i)
        {
            res += abs(list1.arr[i] - list2.arr[i]);
        }
        printf("result parte 1 = %d\n", res);
    }

    if (strcmp(parte, "parte2") == 0 || strcmp(parte, "all") == 0){
        qsort(list1.arr, list2.index, sizeof(int), compare);
        int max = list1.arr[list1.index-1];
        int tmp[max+1];

        for(size_t i=0; i <= max; ++i){
            tmp[i] = 0;
        }

        for(size_t i=0; i < list2.index; ++i){
            if (list2.arr[i] > max) continue;
            tmp[list2.arr[i]] += 1;
        }

        int res = 0;
        for(size_t i=0; i < list1.index; ++i){
            res += list1.arr[i] * tmp[list1.arr[i]];
        }
        printf("result parte 2 = %d\n", res);
    }

    fclose(f);
    free(list1.arr);
    free(list2.arr);
    return 0;
}
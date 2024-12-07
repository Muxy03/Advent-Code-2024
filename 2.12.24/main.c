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

void fill_list(DA *list, const char *str)
{
    char *token = strtok(strdup(str), " ");
    while (token != NULL)
    {
        da_append(list, atoi(token));
        token = strtok(NULL, " ");
    }
    free(token);
}

bool diff_range(int a, int b)
{
    return (abs(a - b) >= 1 && abs(a - b) <= 3);
}

bool check_safe(int sign_of_list, int sign_of_diff, int diff)
{
    return ((sign_of_list == sign_of_diff) && (diff >= 1 && diff <= 3));
}

bool is_safe(DA *list, bool skip)
{
    int prev = list->arr[0];
    size_t i = 1;

    if(skip == false){
        prev = list->arr[1];
        i = 2;
    }

    int sign_list = list->arr[i] - list->arr[i+1] > 0 ? 1 : list->arr[i] - list->arr[i+1] == 0 ? 0 : -1;
    printf(" 1 ricerca di sign_list : %d -> %d - %d\n", sign_list, list->arr[i], list->arr[i+1]);

    int j = i;
    while (sign_list == 0 || !diff_range(list->arr[j], list->arr[j+1]))
    {
        j++;
        sign_list = list->arr[j] - list->arr[j+1] > 0 ? 1 : list->arr[j] - list->arr[j+1] == 0 ? 0 : - 1;
        printf("ricerca di sign_list : %d -> %d - %d\n", sign_list, list->arr[j], list->arr[j + 1]);
    }

    for (; i < *(list->index); ++i)
    {
        int diff = prev - list->arr[i];
        int sign_diff = diff > 0 ? 1 : -1;

        if ((sign_list == sign_diff) && (abs(diff) >= 1 && abs(diff) <= 3))
        {
            prev = list->arr[i];
        }
        else if (!skip)
        {
            return false;
        }
        else
        {
            printf("valore brutto list[%ld] = %d\n",i,list->arr[i]);
            skip = false;
        }
    }

    return true;
}

void print_list(DA *list, size_t init){
    for (size_t i = init; i < *(list->index); ++i)
    {
        printf("list[%ld] = %d\n",i,list->arr[i]);
    }
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
        int count_safe = 0;
        char *line = NULL;
        size_t len = 0;
        int index_line = 1;

        while (getline(&line, &len, f) != EOF)
        {
            fill_list(list, line);

            bool safe = true;

            if (!diff_range(list->arr[0], list->arr[1]))
            {
                safe = false;
            }
            else
            {
                int sign_of_list = list->arr[0] - list->arr[1] > 0 ? 1 : -1;

                for (size_t i = 1; i < *(list->index) - 1; ++i)
                {
                    int sign_of_diff = list->arr[i] - list->arr[i + 1] > 0 ? 1 : -1;
                    int diff = abs(list->arr[i] - list->arr[i + 1]);

                    if ((sign_of_list != sign_of_diff) || !(diff >= 1 && diff <= 3))
                    {
                        safe = false;
                        break;
                    }
                }
            }

            if (safe)
            {
                count_safe++;
            }

            *(list->index) = 0;
            index_line++;
        }
        free(line);
        printf("result parte 1 = %d\n", count_safe);
    }

    if (strcmp(parte, "parte2") == 0 || strcmp(parte, "all") == 0)
    {
        int count_safe = 0;
        char *line = NULL;
        size_t len = 0;
        int index_line = 1;

        while (getline(&line, &len, f) != EOF)
        {
            fill_list(list, line);


            if (is_safe(list, true) || is_safe(list, false))
            {
                count_safe++;
            }

            *(list->index) = 0;
            index_line++;
        }
        free(line);
        printf("result parte 2 = %d\n", count_safe);
    }

    fclose(f);
    free(list->arr);
    return 0;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

/*
const char *pattern = "mul\\([0-9]+,[0-9]+\\)";

    regex_t regex;
    regmatch_t match[1];

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Errore nella compilazione della regex\n");
    }

    while ((ret = regexec(&regex, str + start, 1, match, 0)) == 0)

     regfree(&regex);

    if (ret != REG_NOMATCH)
    {
        fprintf(stderr, "Errore nell'esecuzione della regex\n");
    }
*/

#define N 100

typedef struct
{
    size_t *index;
    size_t capacity;
    char **arr;
} DA;

void da_append(DA *list, char *str)
{
    if (*(list->index) >= list->capacity)
    {
        list->capacity += N;
        list->arr = realloc(list->arr, list->capacity * sizeof(char *));
    }
    list->arr[*(list->index)] = strdup(str);
    *(list->index) += 1;
}

void free_list(DA *list)
{
    for (size_t i = 0; i < *(list->index); ++i)
    {
        free(list->arr[i]);
    }

    free(list->arr);
    free(list);
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

    list->arr = malloc(N * sizeof(char *));
    size_t index = 0;
    list->index = &index;
    list->capacity = N;

    if (strcmp(parte, "parte1") == 0 || strcmp(parte, "all") == 0)
    {
        const char *pattern = "XMAS|SAMX";
        int ret = 0;

        regex_t regex;
        regmatch_t match[1];

        size_t count_line = 1;

        for (char c = getc(f); c != EOF; c = getc(f))
        {
            if (c == '\n')
            {
                count_line++;
            }
        }
        printf("number of lines = %ld\n", count_line);

        fseek(f, 0, SEEK_END);
        long length = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *text = malloc(length * sizeof(char) + 1);
        fread(text, 1, length, f);
        text[length] = '\0';

        printf("%s\n", text);

        if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
        {
            fprintf(stderr, "Errore nella compilazione della regex\n");
        }

        if ((ret = regexec(&regex, text, 1, match, 0)) == 0)
        {
            // printf("trovato XMAS %ld\n", *(list->index) - 1);
        }
        else
        {
            // fprintf(stderr, "Errore nell'esecuzione della regex\n");
        }
        // while (getline(&line, &len, f) != EOF)
        // {
        //     da_append(list, line);

        // }
        regfree(&regex);
        free(text);

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
    free_list(list);
    return 0;
}
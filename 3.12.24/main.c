#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

#define N 100

typedef struct
{
    int *arr;
    size_t *index;
    size_t capacity;
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

void free_list(DA *list)
{
    free(list->arr);
    free(list);
}

void fill_list_1(DA *list, const char *str)
{
    const char *pattern = "mul\\([0-9]+,[0-9]+\\)";

    regex_t regex;
    regmatch_t match[1];
    int start = 0;
    int ret = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Errore nella compilazione della regex\n");
    }

    while ((ret = regexec(&regex, str + start, 1, match, 0)) == 0)
    {
        int start_match = match[0].rm_so + start;
        int end_match = match[0].rm_eo + start;

        int a = 0;
        int b = 0;

        char coppia[end_match - start_match + 1];
        snprintf(coppia, end_match - start_match + 1, "%s", str + start_match);

        sscanf(coppia, "mul(%d,%d)", &a, &b);
        da_append(list, a);
        da_append(list, b);

        start = end_match;
    }

    regfree(&regex);

    if (ret != REG_NOMATCH)
    {
        fprintf(stderr, "Errore nell'esecuzione della regex\n");
    }
}

void fill_list_2(DA *list, const char *str)
{
    const char *pattern1 = "mul\\([0-9]+,[0-9]+\\)";
    const char *pattern2 = "do\\(\\)|don't\\(\\)";

    regex_t regex;
    regex_t regex1;
    regmatch_t match[1];
    regmatch_t match1[1];
    bool ok = true;
    int start = 0;
    int ret = 0;

    if (regcomp(&regex, pattern1, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Errore nella compilazione della regex\n");
    }

    if (regcomp(&regex1, pattern2, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Errore nella compilazione della regex\n");
    }

    while ((ret = regexec(&regex, str + start, 1, match, 0)) == 0)
    {
        int start_match = match[0].rm_so + start;
        int end_match = match[0].rm_eo + start;

        char match_str[start_match - start + 1];
        snprintf(match_str, start_match - start + 1, "%s", str + start);

        int start1 = 0;
        while ((ret = regexec(&regex1, match_str + start1, 1, match1, 0)) == 0)
        {
            int start_match = match1[0].rm_so;
            int end_match = match1[0].rm_eo;

            char do_dont[end_match - start_match + 1];

            snprintf(do_dont, end_match - start_match + 1, "%s", match_str + start_match);

            if (strcmp(do_dont, "do()") == 0)
            {
                ok = true;
            }
            else if (strcmp(do_dont, "don't()") == 0)
            {
                ok = false;
            }

            start1 = end_match;
        }

        if (ok)
        {
            int a = 0;
            int b = 0;

            char coppia[end_match - start_match + 1];
            snprintf(coppia, end_match - start_match + 1, "%s", str + start_match);

            // printf("%s\n", coppia);

            sscanf(coppia, "mul(%d,%d)", &a, &b);
            da_append(list, a);
            da_append(list, b);
        }

        start = end_match;
    }

    regfree(&regex);
    regfree(&regex1);

    if (ret != REG_NOMATCH)
    {
        fprintf(stderr, "Errore nell'esecuzione della regex\n");
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Use : ./main part1 | part2 | all\n");
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
            fill_list_1(list, line);
        }
        free(line);

        int result = 0;
        for (size_t i = 0; i < *(list->index) - 1; i += 2)
        {
            result += (list->arr[i] * list->arr[i + 1]);
        }
        printf("result parte 1 = %d\n", result);
    }

    fseek(f, 0, SEEK_SET);

    if (strcmp(parte, "parte2") == 0 || strcmp(parte, "all") == 0)
    {
        fseek(f, 0, SEEK_END);
        long length = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *text = malloc(length * sizeof(char) + 1);
        fread(text, 1, length, f);
        text[length] = '\0';

        fill_list_2(list, text);

        int result = 0;
        for (size_t i = 0; i < *(list->index) - 1; i += 2)
        {
            result += (list->arr[i] * list->arr[i + 1]);
        }
        free(text);
        printf("result parte 2 = %d\n", result);
    }

    fclose(f);
    free_list(list);
    return 0;
}
#define _GNU_SOURCE  /* See feature_test_macros(7) */
#include <stdio.h>   // permette di usare scanf printf etc ...
#include <stdlib.h>  // conversioni stringa/numero exit() etc ...
#include <stdbool.h> // gestisce tipo bool (variabili booleane)
#include <assert.h>  // permette di usare la funzione assert
#include <string.h>  // confronto/copia/etc di stringhe
#include <errno.h>
#include <unistd.h> // per sleep
#include <fcntl.h>  /* For O* constants */
#include <ctype.h>

char *strrstr(char *line, char *str)
{
    char *res = NULL;
    char *t = strdup(line);
    while (1)
    {
        if (strstr(t, str) == NULL)
        {
            break;
        }
        char *p = strstr(t, str);
        res = strdup(p);
        char *temp = strdup(p);
        strcpy(t, temp + strlen(str));
    }
    return res;
}

int main(int argc, char **argv)
{
    FILE *f = fopen("test1.txt", "r");
    char *LetterNumbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    char *line;
    size_t len;
    int tot = 0;
    int count = 1;
    while (getline(&line, &len, f) != -1)
    {
        char partial[3];
        int imin = 0;
        int imax = 0;
        char *min = NULL;
        char *max = NULL;
        for (int i = 0; i < 10; i++)
        {
            char *first = strstr(line, LetterNumbers[i]);
            char *last = strrstr(line, LetterNumbers[i]);

            if (first != NULL)
            {
                if (min == NULL || strlen(first) > strlen(min))
                {
                    min = strdup(first);
                    imin = i;
                }
                if (max == NULL || strlen(first) < strlen(max))
                {
                    max = strdup(first);
                    imax = i;
                }
            }
            if (first != last)
            {
                if (last != NULL)
                {
                    if (min == NULL || strlen(last) > strlen(min))
                    {
                        min = strdup(last);
                        imin = i;
                    }
                    if (max == NULL || strlen(last) < strlen(max))
                    {
                        max = strdup(last);
                        imax = i;
                    }
                }
            }
        }
        strcpy(&partial[0], LetterNumbers[imin]);
        strcpy(&partial[1], LetterNumbers[imax]);
        partial[2] = '\0';
        printf("%d)%d+%d\n", count++, tot, atoi(partial));
        tot += atoi(partial);
    }
    fclose(f);
    printf("tot: %d\n", tot);
    return 0;
}
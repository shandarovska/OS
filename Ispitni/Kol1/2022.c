/*Да се напише програма во C која работи со процеси и нитки. Програмата (главната
нитка) како аргументи од командна линија добива збор што се пребарува и листа од
имиња на датотеки. Доколку не добие листа од датотеки од командна линија (добие
само збор за пребарување), програмата треба да му дозволи да внесе имиња на 3
датотеки од тастатура. Доколку нема ни збор за пребарување, најпрво го внесува зборот
од тастатура, а потоа имињата на 3те датотеки. За секоја датотека во која се прави
пребарување, се креира посебна нитка која го прави пребарувањето, притоа, на секоја
нитка ѝ се испраќа кој е зборот што треба да го пребарува и името на датотеката во која
треба да го прави пребарувањето. Секоја нитка го пребарува зборот во својата датотека,
и штом заврши, на екран го печати името на датотеката и колку пати се појавил зборот.
Откако ќе завршат сите нитки, главната нитка на екран печати, за секоја датотека
одделно, колку процентуално се појавил зборот во таа датотека (процент од вкупното
појавување на зборот во сите датотеки).*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
// #include <sys/wait.h>
#define max_w 100
#define max_f 3

typedef struct
{
    FILE *file;
    char filename[max_w], search_word[max_w];
    int count;
    char line[1024];
} thread_arg;

void *func(void *t)
{
    thread_arg data = *((thread_arg *)t);
    char line[1024];
    int word_count = 0, word_len = strlen(data.search_word);

    while (fgets(line, 1024, data.file))
    {
        char *position = line;
        while ((position = strstr(position, data.search_word)) != NULL)
        {
            word_count++;
            position += word_len;
        }
    }
}

int main(int argc, char *argv[])
{

    char filename[max_w], search_word[max_w];
    int number_files = 0, total_count = 0;

    if (argc < 2)
    {
        printf("Vnesete zbor za prebaruvanje!");
        scanf("%s", search_word);

        printf("Vnesete iminja na 3 datoteki: ");
        for (int i = 0; i < 3; i++)
            scanf("%s", filename[i]);
    }
    else
    {
        strcpy(search_word, argv[1]);
        number_files = argc - 1;

        for (int i = 0; i < number_files; i++)
            strcpy(filename[i], argv[i + 2]);
    }

    FILE *files[max_f];
    for (int i = 0; i < number_files; i++)
    {
        files[i] = fopen(filename[i], "r");
        if (!files[i])
        {
            printf("Ne mozhe da se otvori datotekata: %s.\n", filename[i]);
            exit(-1);
        }
    }

    thread_arg args[max_f];
    pthread_t nitki[max_f];

    for (int i = 0; i < number_files; i++)
    {

        args[i].file = files[i];
        strcpy(args[i].filename, filename[i]);
        strcpy(args[i].search_word, search_word);
        args[i].count = 0;

        if (pthread_create(&nitki[i], NULL, func, (void *)&args[i]))
        {
            printf("Greshka.");
            exit(-1);
        }
    }

    for (int i = 0; i < number_files; i++)
        pthread_join(&nitki[i], NULL);

    printf("Vkupno pojavuvanja: %d\n", total_count);
    for (int i = 0; i < number_files; i++)
    {
        printf("Datoteka: %s, Pojavuvanja %d.\n", args[i].filename, args[i].count);
        total_count += args[i].count;
    }

    for (int i = 0; i < number_files; i++)
    {
        if (total_count > 0)
        {
            float perc = (args[i].count / (float)total_count) * 100;
            printf("Datotekata: %s, procent: %.2f.\n", args[i].filename, perc);
        }
    }

    return 0;
}
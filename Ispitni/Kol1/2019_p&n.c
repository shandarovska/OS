/*Да се напише програма во C која работи со процеси и нитки. Главната програма (главната нитка) како
аргумент добива име на влезна датотека. Главната нитка треба да креира онолку нитки колку што треба,
така што, секоја нитка да добие по 10 линии од влезната датотека (нема повеќе од 1000 линии, а притоа
последната нитка може да добие и помалку од 10 линии). Секоја една од нитките, ги изминува своите 10
линии од датотеката и брои колку има големи а колку мали букви. Откако ќе завршат нитките, главната
нитка печати на екран колку секоја нитка нашла големи и мали букви и печати колку вкупно големи и
мали букви биле пронајдени. Не е дозволено содржината на целата датотека да биде прочитана во низа
т.е. секоја од нитките мора да работи со FILE * покажувач за изминување на датотеката т.е. на линиите
од датотеката. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
// #include <sys/wait.h>
#define max_l 1000
#define lines_per_thread 10

typedef struct
{
    int thread_id;
    FILE *file;
    int pochetna_l, linii_za_chitanje, uppercase, lowercase;
} ThreadData;

void *func(void *arg)
{
    ThreadData arg1 = *((ThreadData *)arg);
    char line[1024];
    int up, low;

    // da se nasochima na pochetokot
    for (int i = 0; i < arg1.pochetna_l; i++)
        fgets(line, 1024, arg1.file);
    // ja procesira sekoja linija
    for (int i = 0; i < arg1.pochetna_l; i++)
    {
        if (fgets(line, 1024, arg1.file) == NULL)
            break; // reached end of file
    }

    for (int j = 0; line[j] != '\n'; j++)
    {
        if (line[j] >= 'A' && line[j] <= 'Z')
            up++;
        else if (line[j] >= 'a' && line[j] <= 'z')
            low++;
    }
    arg1.lowercase = low;
    arg1.uppercase = up;

    // se printaat

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Nedovolno argumenti!");
        exit(-1);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Ne postoi taa datoteka!");
        exit(-1);
    }
    int total_lines = 0;
    char lines[1024];

    while (fgets(lines, sizeof(lines), file) != NULL)
        total_lines++; // presmetuvanje na linii vo datoteka

    rewind(file); // da se vrati pokazhuvashot na pochetok na datotekata

    int num_threads = total_lines / lines_per_thread;
    pthread_t nitki[num_threads];
    ThreadData arg[num_threads];
    for (int i = 0; i < num_threads; i++)
    {
        arg[i].thread_id = i;
        arg[i].file = file;
        arg[i].pochetna_l = i * lines_per_thread;

        if (i == num_threads - 1) // dokolku sme na poslednata linija
            arg->linii_za_chitanje = total_lines - (i * lines_per_thread);
        else
            arg[i].linii_za_chitanje = lines_per_thread;

        if (pthread_create(&nitki[i], NULL, func, (void *)&arg[i]))
        {
            printf("Greshka!");
            exit(-1);
        }
    }

    int total_upp = 0, total_low = 0;
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(nitki[i], NULL);
        total_upp += arg[i].uppercase;
        total_low += arg[i].lowercase;
    }
    printf("Total uppercase letters: %d", total_upp);
    printf("Total lowercase letters: %d", total_low);

    fclose(file);

    return 0;
}
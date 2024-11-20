/*Да се напише програма за пребарување на најголемиот елемент во низа од 1000
случајно генерирани броеви. Програмата треба да креира 10 нитки кои што најпрво ќе
генерираат 1000 броеви (секоја по 100). Потоа, треба да се креираат нови 10 нитки
кои што ќе ги изминат тие 1000 (секоја своите 100) и ќе го најдат најголемиот
елемент. На крај, главната програма треба да го испише најголемиот генериран број.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define MAX_NITKI 10
// #include <sys/wait.h>
int pole[1000], maxpole[10];

void *func(void *t)
{
    int id = *((int *)t);
    for (int i = id * 100; i < id * 100; i++)
    {
        pole[i] = rand() % 5000; // kje dodeli random vrednost od 0 - 4999
                                 // pole[0] = 319, pole[1] = 41... pole[99] = 1240 - za prva nitka
                                 // pole [100] = 4721... pole[199] = 9 - za vtora nitka i t.n.
    }
    pthread_exit(NULL);
}

void *prebaraj(void *t)
{
    int id = *((int *)t);
    int max = pole[id * 100]; // max go definira na prviot za da sporedi
    for (int i = id * 100; i < id * 100 + 100; i++)
    {
        if (pole[i] > max)
            max = pole[i];
    }
    maxpole[id] = max;
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t nitki[MAX_NITKI];
    int t[10], rc1, rc2;

    for (int i = 0; i < MAX_NITKI; i++)
    {
        t[i] = i; // niza koja gi chuva broevite na nitkite
        rc1 = pthread_create(&nitki[i], NULL, func, (void *)&t[i]);
        if (rc1)
        {
            printf("Greshka");
            exit(-1);
        }
    }

    for (int i = 0; i < MAX_NITKI; i++) // chekame nitkite da se kreiraat
        pthread_join(nitki[i], NULL);

    for (int i = 0; i < MAX_NITKI; i++)
    {
        t[i] = i;
        if (pthread_create(&nitki[i], NULL, prebaraj, (void *)i))
        {
            printf("Greshka");
            exit(-1);
        }
    }

    for (int i = 0; i < MAX_NITKI; i++) // chekame nitkite da se kreiraat
        pthread_join(nitki[i], NULL);

    int max = maxpole[0];
    for (int i = 1; i < MAX_NITKI; i++)
    {
        if (maxpole[i] > max)
            max = maxpole[i];
    }
    printf("Najgolemiot generiran broj e %d.", max);
    return 0;
}
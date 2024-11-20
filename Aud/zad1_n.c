/*Да се напише програма која ќе креира 5 нитки. Секоја од нитките да го отпечати на
екран својот реден број. Дали при секое извршување на програмата, ист е редоследот
на печатење на екран? Зошто? Од што зависи?*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
// #include <sys/wait.h>
void *func(void *t)
{
    int i = *((int *)t);
    printf("Jas sum nitka %lu dobiv broj %d\n", pthread_self(), i);
    pthread_exit(NULL);
}

int main(int agrc, char *argv[])
{
    pthread_t threads[10]; // niza koja kje ni gi drzhi id na nitki
    int rc1;
    long t;
    void *status;
    int b[5];
    for (t = 0; t < 5; t++)
    {
        printf("Kreiranje na nitka %d", t);
        b[t] = t;
        rc1 = pthread_create(&threads[t], NULL, func, (void *)&b[t]);
        if (rc1)
        {
            printf("Error, return od pthreads_create() e %d\n", rc1);
            exit(-1);
        }
    }

    for (t = 0; t < 5; t++)
    {
        rc1 = pthread_join(threads[t], &status);
        if (rc1)
        {
            printf("Error, return od pthreads_create() e %d\n", rc1);
            exit(-1);
        }
        printf("Main?: complete join with thread %ld having status of %ld", t, (long)status);
    }
    pthread_exit(NULL);

    return 0;
}
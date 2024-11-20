/*Да се напишат две програми во C кои работат со процеси и нитки. Првата програма се
повикува од конзола и притоа како аргумент (од командна линија) се испраќа број „N“, кој
кажува колку броеви има во низата и број „К“ кој кажува кој број треба да се пребара.
Потоа, првата програма ја стартува втората програма како аргумент од командна линија ги
испраќа вредносите „N“ и „К“. Двата процеси (програми) креираат по 5 нитки кои ја
пребаруваат вредноста „К“ во низа од „N“ цели броеви. Низата е запишана во датотека со
име „dat.txt“ притоа се запишани цели броеви помеѓу себе оделени со празно место.
Главните нитки на двата процеси ја исчитуваат датотеката и ги сместуваат броевите во
низа. Потоа, секоја од дополнителните 5 нитки од двата процеси генерира случаен индекс
од низата од N цели броеви и проверува дали е на таа позиција во низата бројот „К“.
Доколку е, тогаш го убива другиот процес и печати дека тој (прв или втор) процес го нашол
елементот и печати на која позиција го нашол елементот. Доколку не е тој елемент,
генерира нов индекс и продолжува со пребарување. Секоја нитка генерира N-пати индекс, и
доколку после тие генерирања не го најде бројот, завршува со работа. Доколку процесот
(првиот или вториот) не го најде бројот со сите свои нитки (сите нитки му завршат без да го
најдат бројот), завршува и тој процес (неговата главна нитка) и печати дека завршил без да
го најде бројот.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
// #include <sys/wait.h>
#define max_nitki 5

int n, k, found = 0;
int niza[100];

void *prebaraj(void *t)
{
    int id = *((int *)t);

    for (int i = 0; i < n; i++)
    {
        if (found)
            pthread_exit(NULL);
    }
    int index = rand() % n;
    if (niza[index] == k)
    {
        printf("Proces 1, nitkata %d go najde brojot %d na poz. %d.", id, k, index);
        found = 1;
        kill(0, SIGTERM);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Nedovolno broj argumenti!");
        exit(-1);
    }
    n = atoi(argv[1]); // from string to integer
    k = atoi(argv[2]);

    FILE *file = fopen("dat.txt", "r");
    if (!file)
    {
        printf("Datotekata ne postoi!");
        exit(-1);
    }

    for (int i = 0; i < n; i++)
        fscanf(file, "&d", &niza[i]);

    pthread_t nitki[max_nitki];
    int t[max_nitki];

    pid_t dete = fork();

    if (dete != 0)
    { // parent
        wait(NULL);
        printf("Proces 1 zavrshi!");
    }
    else
    {
        execl("./zad1", "zad1", argv[1], argv[2], NULL);
        printf("Neushpeshno startuvanje na vtora programa!");
        exit(-1);
    }

    for (int i = 0; i < n; i++)
    {
        t[i] = i;
        if (pthread_create(&nitki[i], NULL, prebaraj, (void *)&t[i]))
        {
            printf("Greshka!");
            exit(-1);
        }
    }
    for (int i = 0; i < n; i++)
        pthread_join(nitki[i], NULL); // da se dochekaat site nitki

    if (!found)
    {
        printf("Procesot 1 ne go najde brojot %d.", k);
        exit(-1);
    }

    return 0;
}
/*
Glavnata programa (roditel processot) dobiva niza od naredbi koi treba da gi izvrshi kako argumenti
od komandna linija. Roditel processot treba, najprvo, da kreira onolku deca procesi kolku shto ima naredbi
navedeno od komandna linija(naredbite se bez argumenti). Potoa treba da se kreira onolku nitki, kolku sto
ima naredbi, taka shto sekoja nitka ke ceka i ke broi kolku sekundi mu bilo potrebno na soodvetniot proces
da zavrshi. Toa znaci deka prvata nitka ke bide zadolzena za prvata naredba(t.e. za prviot process),
vtorata za vtoriot itn. Sekoja nitka broi kolku vreme se izvrshuval nejziniot process(naredba) i koga ke
zavrshi, kazuva kolku vkupni sekundi mu trebalo da zavrshi. Potoa i samata nitka zavrshuva. Otkako ke
zavrshat site processi/nitki, togash glavniot process/nitka, pecati na ekran kolku vreme i trebalo na
sekoja naredba da se izvrshi.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
// #include <sys/wait.h>

void *func(void *t)
{
    int id = (*(int *)t), s = 0;

    while (waitpid(deca[id], NULL, WNOHANG) != deca[id]) // mora da go chekame, koga kje zavrshi deteto go vrakja istiot id,
    {                                                    // i togash znaeme deka zavrshil
        sleep(1);
        s++;
    }
    vreme[id] = s;
    pthread_exit(NULL);
}

pid_t deca[100];
int vreme[100];

int main(int argc, char *argv[])
{

    int n = argc - 1; // broj na argumenti
    pthread_t nitki[n];
    int i;
    int t[n];

    // kreiranje na deca procesi
    for (i = 0; i < n; i++)
    {
        deca[i] = fork();
        if (deca[i] == 0)
        { // dete procesot
            execlp(argv[i + 1], &argv[i + 1], NULL);
            printf("Greshka!");
            exit(-1);
        }
        else if (deca[i] < 0)
        {
            printf("Fork() ne uspea!");
            exit(-1);
        }
    }

    for (i = 0; i < n; i++)
    {
        t[i] = i;
        if (pthread_create(&nitki[i], NULL, func, (void *)&t[i]))
        {
            printf("Greshka!");
            exit(-1);
        }
    }

    for (i = 0; i < n; i++)
        pthread_join(nitki[i], NULL);

    for (i = 0; i < n; i++)
        printf("Command '%s' i trebashe %d sekundi", argv[i + 1], vreme[i]);

    return 0;
}

/* Да се напише C програма која ќе направи N пати извршување на некоја наредба. Родител
процесот најпрво од тастатура го вчитува бројот колку пати ќе се изврши наредбата.
Самата наредба се внесува како аргумент од командна линија и може да има непознат
(променлив) број на аргументи. Родител процесот потоа ги креира останатите N процеси,
секој еден од тие N процеси ја извршува наредбата, и чека секој еден од нив да заврши.
Кога ќе заврши и последниот процес, родителот ја испишува пораката: “Zavrshuva process 0” */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/wait.h>

int main(int argc, char *argv[])
{
    int n;
    scanf("%f", &n);

    if (argc < 2)
    {
        printf("Nedovolen broj argumenti!");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        pid_t dete = fork(); // kreirame deca
        if (dete == 0)
        { // dete proces ima ip 0
            execvp(argv[1], &argv[1]);
            printf("Greshka");
            exit(1);
        }
    }

    for (int i = 0; i < n; i++)
        wait(NULL); // roditelot gi cheka site deca da zavrshuat

    printf("Zavrshuva proces 0\n");
    return 0;
}

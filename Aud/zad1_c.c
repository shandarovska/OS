/*Да се напише програма која како аргумент добива команда која
треба да ја изврши.
Програмата треба да изврши замена на стандардниот знак „&“
со „%“ за започнување на програма како позадински или преден
процес*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        print("Nedovolen broj argumenti!");
        return 0;
    }
    int len = strlen(argv[argc - 1]); // go zimame lengthot na posledniot element

    int towait = 1;
    if (len == 1 && argv[argc - 1][0] == '&') // dokolku se razdeleni
    {
        argv[argc - 1][0] = "%";
        towait = 0;
    }
    else if (argv[argc - 1][len - 1] == '&')
    { // len - 1 e posledniot char
        argv[argc - 1][len - 1] == "%";
        towait = 0;
    }
    pid_t dete = fork();
    if (dete == 0)
    {
        execvp(argv[1], &argv[1]);
        printf("Greshka");
        exit(-1);
    }

    if (towait)
        wait(NULL); // site deca da zavrshat

    return 0;
}
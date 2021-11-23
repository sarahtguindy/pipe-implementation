#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>

using namespace std;

int main(int argc, char **argv)
{
    // Handle command line arguments
    const int LEN = 32;
    char argument1[LEN];
    char argument2[LEN];
    strcpy(argument1, argv[1]);
    strcpy(argument2, argv[2]);
    char arg1[3][LEN];
    char arg2[3][LEN];
    int len1 = 0, len2 = 0;

    char *token = strtok(argument1, " ");
    while (token != NULL)
    {
        strcpy(arg1[len1], token);
        token = strtok(NULL, " ");
        ++len1;
    }
    token = strtok(argument2, " ");
    while (token != NULL)
    {
        strcpy(arg2[len2], token);
        token = strtok(NULL, " ");
        ++len2;
    }

    int pfd1[2], pfd2[2];
    pid_t pid1, pid2;

    // Child process
    if (pipe(pfd1) == -1)
    {
        perror("pipe");
    }

    pid1 = fork();
    if (pid1 == 0)
    {
        if (dup2(pfd1[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
        }

        if (close(pfd1[0]) == -1)
        {
            perror("close");
        }

        if (close(pfd1[1]) == -1)
        {
            perror("close");
        }

        // The number of agruments will determine which execlp() to use
        switch (len1)
        {
        case 1:
            execlp(argument1, argument1, (char *)NULL);
            break;
        case 2:
            execlp(argument1, argument1, arg1[1], (char *)NULL);
            break;
        case 3:
            execlp(argument1, argument1, arg1[1], arg1[2], (char *)NULL);
            break;
        default:
            break;
        }

        perror("execlp");
    }

    // Parent process
    pid2 = fork();
    if (pid2 == 0)
    {
        if (dup2(pfd1[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
        }

        if (close(pfd1[0]) == -1)
        {
            perror("close");
        }

        if (close(pfd1[1]) == -1)
        {
            perror("close");
        }

        // The number of agruments will determine which execlp() to use
        switch (len2)
        {
        case 1:
            execlp(argument2, argument2, (char *)NULL);
            break;
        case 2:
            execlp(argument2, argument2, arg2[1], (char *)NULL);
            break;
        case 3:
            execlp(argument2, argument2, arg2[1], arg2[2], (char *)NULL);
            break;
        default:
            break;
        }

        perror("execlp");
    }

    // Close file descriptors
    // Child should not reach this point
    if (close(pfd1[0]) == -1)
    {
        perror("close");
    }
    if (close(pfd1[1]) == -1)
    {
        perror("close");
    }

    if (waitpid(pid1, NULL, 0) == -1)
    {
        perror("waitpid");
    }
    if (waitpid(pid2, NULL, 0) == -1)
    {
        perror("waitpid");
    }
}

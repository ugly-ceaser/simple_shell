#include "shell.h"
#include <sys/wait.h>

#define MaxVAlue 10

/**
 * fetch - read input from the user and execute the command
 * @arg_vector: array of strings containing the command-line arguments
 * @env_variable: array of strings containing the environment variables
 *
 * Return: None.
 */
void fetch(char **arg_vector, char **env_variable)
{

    char *Data = NULL;
    int Checker, Progress_Status, Counter;
    size_t Num = 0;
    ssize_t Char_Counter;
    char *Arg_vector[MaxVAlue];
    pid_t Child_Process;

    while (1)
    {
        /* If standard input is a terminal, display a prompt */
        if (isatty(STDIN_FILENO))
            printf("waiting...");

        /* Read input from the user */
        Char_Counter = getline(&Data, &Num, stdin);

        /* If getline fails, exit with a failure status */
        if (Char_Counter == -1)
        {
            free(Data);
            exit(EXIT_FAILURE);
        }

        /* Replace the newline character with a null character */
        Checker = 0;
        while (Data[Checker])
        {
            if (Data[Checker] == '\n')
                Data[Checker] = 0;
            Checker++;
        }

        Counter = 0;

        /* Set the command to be executed */
        Arg_vector[Counter] = strtok(Data, " ");

        /* Parse the input string into an array of arguments */
        while (Arg_vector[Counter] != NULL)
        {
            Arg_vector[++Counter] = strtok(NULL, " ");
        }

        /* Create a child process to execute the command */
        Child_Process = fork();

        /* If fork fails, exit with a failure status */
        if (Child_Process == -1)
        {
            free(Data);
            exit(EXIT_FAILURE);
        }

        /* If this is the child process, execute the command */
        if (Child_Process == 0)
        {
            if (execve(Arg_vector[0], Arg_vector, env_variable) == -1)
            {
                /* If execve fails, print an error message to the console */
                printf("%s :Operation failed\n", arg_vector[0]);
            }
        }
        /* If this is the parent process, wait for the child to finish */
        else
        {
            wait(&Progress_Status);
        }
    }
}

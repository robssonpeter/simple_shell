#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARG_LENGTH 20
#define MAX_ARGS 10

/**
 * main - Simple shell program that reads a command from standard input,
 *        parses it into arguments, and executes it as a child process.
 *
 * Return: Always 0.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *argv[MAX_ARGS + 1]; /* +1 for NULL at the end */
	char *envp[] = {NULL};
	int status;

	while (1)
	{
		/* Print prompt and read user input */
		printf("$ ");
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			/* End of file condition (Ctrl+D) */
			printf("\n");
			break;
		}

		/* Remove newline character at the end of the command */
		command[strcspn(command, "\n")] = 0;

		/* Parse command line into arguments */
		int argc = 0;
		char *arg = strtok(command, " ");
		while (arg != NULL && argc < MAX_ARGS)
		{
			argv[argc++] = arg;
			arg = strtok(NULL, " ");
		}
		argv[argc] = NULL;

		/* Fork a new process to execute the command */
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		else if (pid == 0)
		{
			/* Child process */
			if (execve(argv[0], argv, envp) == -1)
			{
				/* Error executing command */
				perror("execve");
				exit(1);
			}
		}
		else
		{
			/* Parent process */
			do {
				/* Wait for child process to finish */
				pid_t wpid = waitpid(pid, &status, WUNTRACED);
				if (wpid == -1)
				{
					perror("waitpid");
					break;
				}
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}

	return (0);
}


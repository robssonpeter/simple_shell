#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "main.h"
#include "find_command.c"

/**
 * main - Runs the shell
 * Return: 0 on success, non-zero on error
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *argv[MAX_ARGS + 1]; /* +1 for NULL at the end */
	char *envp[] = { NULL };
	int status, argc;
	char *arg, *path, *fullpath;

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

		/* Check for built-in commands */
		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		else if (strcmp(command, "env") == 0)
		{
			/* Print environment variables */
			char **ep;

			for (ep = environ; *ep != NULL; ep++)
			{
				printf("%s\n", *ep);
			}
			continue;
		}

		/* Parse command line into arguments */
		argc = 0;
		arg = strtok(command, " ");
		while (arg != NULL && argc < MAX_ARGS)
		{
			argv[argc++] = arg;
			arg = strtok(NULL, " ");
		}
		argv[argc] = NULL;

		/* Check if the command exists */
		path = getenv("PATH");
		fullpath = find_command(argv[0], path);
		if (fullpath == NULL)
		{
			printf("Command not found\n");
			continue;
		}

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
		if (execve(fullpath, argv, envp) == -1)
		{
			/* Error executing command */
			perror("execve");
			exit(1);
		}
	}
	else
	{
		do {
			pid_t wpid = waitpid(pid, &status, WUNTRACED);

			if (wpid == -1)
			{
				perror("waitpid");
				break;
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(fullpath);
	}
	return (0);
}

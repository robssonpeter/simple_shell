#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * main - the function
 * Description: the artificial shell
 * Return: Void
 */
int main(void)
{
	char *command = NULL;
	size_t size = 0;
	char *commands[20] = {"/bin/ls", NULL};
	char *cleaned_command = malloc(30);
	int index;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		getline(&command, &size, stdin);
		index = 0;
		pid = fork();
		while (*(command + index) != '\n')
		{
			*(cleaned_command + index) = *(command + index);
			index++;
		}
		*commands = command;
		if (pid == -1)
		{
			printf("process was not completed\n");
		}
		else if (pid == 0)
		{
			if (execve(cleaned_command, commands, NULL) == -1)
				perror("Error");
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}


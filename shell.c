#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
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
	char *token;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		getline(&command, &size, stdin);
		index = 0;
		while (*(command + index) != '\n')
		{
			*(cleaned_command + index) = *(command + index);
			index++;
		}

		token = strtok(cleaned_command, " ");
		*commands = token;
		index = 0;
		while (token != NULL)
		{
			*(commands + index) = token;
			token = strtok(NULL, " ");
			index++;
		}

		pid = fork();
		if (pid == -1)
		{
			printf("process was not completed\n");
		}
		else if (pid == 0)
		{
			if (execve(*commands, commands, NULL) == -1)
				perror("Error");
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
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
			*(cleaned_command+index) = *(command + index);
			index++;
		}
		/* close the shell if exit word is found*/

	
		*commands = command;

		if (pid == -1)
		{
			// proces was not succesful
			printf("process was not completed\n");
		}
		else if (pid == 0)
		{
			// child process is executing
			if (execve(cleaned_command, commands, NULL) == -1)
				perror("Error");
		}
		else
		{
			wait(NULL);
			// the main process continues
			/*printf("Hello %s", cleaned_command);*/
			/*return (0);*/
		}
	}
	return (0);
}


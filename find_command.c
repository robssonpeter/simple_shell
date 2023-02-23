#include "main.h"
#include <stdlib.h>

/**
 * find_command - Finds a command in the given path
 * @command: The command to find
 * @path: The path to search for the command
 *
 * Return: The full path to the command, or NULL if the command was not found
 */
char *find_command(char *command, char *path)
{
	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		char *fullpath = malloc(strlen(dir) + strlen(command) + 2);

		sprintf(fullpath, "%s/%s", dir, command);
		if (access(fullpath, X_OK) == 0)
		{
			return (fullpath);
		}
		free(fullpath);
		dir = strtok(NULL, ":");
	}
	return (NULL);
}

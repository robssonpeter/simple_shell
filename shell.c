#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
/**
 * main - the function
 * Description: the artificial shell
 * Return: Void
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *argv[] = { NULL };
	char *envp[] = { NULL };
	int status;

	while (1) {
	// Print prompt and read user input
	printf("> ");
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
		// End of file condition (Ctrl+D)
		printf("\n");
		break;
	}

	// Remove newline character at the end of the command
	command[strcspn(command, "\n")] = 0;

	// Fork a new process to execute the command
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		continue;
	} else if (pid == 0) {
		// Child process
		if (execve(command, argv, envp) == -1) {
			// Error executing command
			perror("execve");
			exit(1);
		}
	} else {
	    // Parent process
		do {
			// Wait for child process to finish
			pid_t wpid = waitpid(pid, &status, WUNTRACED);
			if (wpid == -1) {
				perror("waitpid");
				break;
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}

	return 0;
}

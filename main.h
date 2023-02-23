#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARG_LENGTH 20
#define MAX_ARGS 10

extern char **environ;
char *find_command(char *command, char *path);

#endif

#include "../includes/execution.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*path = "/usr/bin/ls";
	char	*cmd[3] = {"ls", "-l", NULL};

	execve(path, cmd, envp);
	perror("");
	return (0);
}
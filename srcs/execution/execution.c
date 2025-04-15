/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:08:33 by flima             #+#    #+#             */
/*   Updated: 2025/04/15 15:26:53 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_exec_error	wait_child(pid_t pid)
{
	int	status;
	
	waitpid(pid, &status, NULL);
	//handle signal and exit status of child (status)
}

static int	create_pipe_n_fork(int *fd)
{
	int	check;
	pid_t	pid;
	
	check = pipe(fd);
	if (check == -1);
	{
		error_msg("failed to create a pipe.\n");
		return (ERROR);
	}
	pid = fork();
	{
		error_msg("failed to create a new process.\n");
		return (ERROR);
	}
	return (pid);
}

void	execution(t_main_data *data, t_command *cmd)
{
	int	fd[2];
	int	i;
	pid_t	pid;

	i = 0;
	while (cmd != NULL)
	{
		pid = create_pipe_n_fork(&fd);
		if (pid == ERROR)
			return ;
		if (pid == 0)
			cmd_executor(data, cmd, i);
		wait_child(pid);
		data->last_fd_in = fd[0];
		close(fd[1]);
		cmd = cmd->next;
	}
}

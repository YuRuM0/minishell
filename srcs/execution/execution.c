/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:08:33 by flima             #+#    #+#             */
/*   Updated: 2025/04/19 16:51:32 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	wait_all_children(t_main_data *data, pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nbr_of_cmds)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
}

static int	create_pipe_n_fork(int *fd)
{
	int	check;
	pid_t	pid;

	check = pipe(fd);
	if (check == -1)
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

void	execution(t_main_data *data, t_command *cmd, char **envp)
{
	int	fd[2];
	int	i;
	pid_t	pid[data->nbr_of_cmds];

	i = 0;
	//set_signals
	while (cmd != NULL)
	{
		pid[i] = create_pipe_n_fork(fd);
		if (pid[i] == ERROR)
			return ; // msg of error (perror)
		if (pid[i] == 0)
			cmd_executor(data, cmd, fd, envp);
		if (data->last_fd_in != STDIN_FILENO)
			close(data->last_fd_in);
		data->last_fd_in = fd[0];
		close(fd[1]);
		cmd = cmd->next;
		i++;
	}
	wait_all_children(data, pid);
}

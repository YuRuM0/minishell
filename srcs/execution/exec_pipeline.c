/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:18:37 by flima             #+#    #+#             */
/*   Updated: 2025/04/22 15:44:37 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	wait_all_children(t_main_data *data, pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	//handle exit code 
	while (i < data->nbr_of_cmds)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	pipeline_status = status;
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
	if (pid == -1)
	{
		error_msg("failed to create a new process.\n");
		return (ERROR);
	}
	return (pid);
}

t_exec_error	execute_pipeline(t_main_data *data, t_command *cmd)
{
	int	fd[2];
	int	i;
	pid_t	pid[data->nbr_of_cmds];

	i = 0;
	while (cmd != NULL)
	{
		pid[i] = create_pipe_n_fork(fd);
		if (pid[i] == ERROR)
			return (ERROR);
		if (pid[i] == 0)
			cmd_executor(data, cmd, fd);
		if (data->last_fd_in != STDIN_FILENO)
			close(data->last_fd_in);
		data->last_fd_in = fd[0];
		close(fd[1]);
		cmd = cmd->next;
		i++;
	}
	wait_all_children(data, pid);
	return (SUCCEED);
}

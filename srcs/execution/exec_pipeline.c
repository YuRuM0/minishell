/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:18:37 by flima             #+#    #+#             */
/*   Updated: 2025/04/22 17:50:26 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	wait_all_children(t_main_data *data, pid_t *pid)
{
	int	i;
	int	exit_status;

	i = -1;
	while (++i < data->nbr_of_cmds)
		waitpid(pid[i], &exit_status, 0);
	if (WEXITSTATUS(exit_status))
	{
		if (set_exit_env_status(data->env_vars, EXIT_FAIL) != SUCCESS)
			status_error(data, ERROR_MEM_ALLOC);
	}
	else if (WIFSIGNALED(exit_status))
		data->exit_status = 128 + WTERMSIG(exit_status);
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

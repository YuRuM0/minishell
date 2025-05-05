/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:18:37 by flima             #+#    #+#             */
/*   Updated: 2025/04/28 20:29:35 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	get_exit_child(t_main_data *data, int exit_status)
{
	if (WIFEXITED(exit_status))
	{
		data->exit_status = WEXITSTATUS(exit_status);
		if (set_exit_env_status(data->env_vars, \
			data->exit_status) != SUCCESS)
			status_error(data, ERROR_MEM_ALLOC);
	}
	else if (WIFSIGNALED(exit_status))
	{
		data->exit_status = 128 + WTERMSIG(exit_status);
		if (set_exit_env_status(data->env_vars, \
			data->exit_status) != SUCCESS)
			status_error(data, ERROR_MEM_ALLOC);
		g_last_signal = data->exit_status;
	}
}

static void	wait_all_children(t_main_data *data)
{
	int		exit_status;
	pid_t	pid;

	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, &exit_status, 0);
		if (pid == data->last_pid)
			get_exit_child(data, exit_status);
	}
}

static t_exec_error	create_pipe_n_fork(t_main_data *data, t_command *cmd)
{
	int		check;

	if (cmd->is_pipe_next == true)
	{
		check = pipe(cmd->fd);
		if (check == -1)
			return (error_msg("failed to create a pipe.\n"), ERROR);
	}
	data->last_pid = fork();
	if (data->last_pid == -1)
		return (error_msg("failed to create a new process.\n"), ERROR);
	return (SUCCEED);
}

t_exec_error	execute_pipeline(t_main_data *data, t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd != NULL)
	{
		if (create_pipe_n_fork(data, cmd) != SUCCEED)
			return (ERROR);
		if (data->last_pid == 0)
			cmd_executor(data, cmd, cmd->fd);
		close_parent_heredoc_fd(cmd->redir_list);
		if (data->last_fd_in != STDIN_FILENO)
			close(data->last_fd_in);
		if (cmd->is_pipe_next == true)
		{
			data->last_fd_in = cmd->fd[0];
			close(cmd->fd[1]);
		}
		cmd = cmd->next;
		i++;
	}
	wait_all_children(data);
	return (SUCCEED);
}

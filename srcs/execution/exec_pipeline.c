/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:18:37 by flima             #+#    #+#             */
/*   Updated: 2025/04/28 15:32:35 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	close_fds_child(t_command *cmd)
{
	if (cmd->infile != NULL)
		close(cmd->infile->fd);
	if (cmd->outfile != NULL)
		close(cmd->outfile->fd);
	if (cmd->fd[0] != -2 && cmd->fd[1] != -2)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	if (cmd->data->last_fd_in != STDIN_FILENO)
		close(cmd->data->last_fd_in);
}

static void	wait_all_children(t_main_data *data)
{
	int	exit_status;
	pid_t	pid;

	while ((pid = waitpid(-1, &exit_status, 0)) > 0)
	{
		if (pid == data->last_pid)
		{
			if (WEXITSTATUS(exit_status))
			{
				data->exit_status = WEXITSTATUS(exit_status);
				if (set_exit_env_status(data->env_vars, data->exit_status) != SUCCESS)
					status_error(data, ERROR_MEM_ALLOC);
			}
			else if (WIFSIGNALED(exit_status))
			{
				data->exit_status = 128 + WTERMSIG(exit_status);
				if (set_exit_env_status(data->env_vars, data->exit_status) != SUCCESS)
					status_error(data, ERROR_MEM_ALLOC);
				g_last_signal = data->exit_status;
			}
		}
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

static void	close_parent_heredoc_fd(t_redir *redir_list)
{
	while (redir_list != NULL)
	{
		if (redir_list && redir_list->redir_id == REDIR_HEREDOC)
			close(redir_list->fd);
		redir_list = redir_list->next;
	}
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

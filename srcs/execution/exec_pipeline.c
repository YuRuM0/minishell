/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:18:37 by flima             #+#    #+#             */
/*   Updated: 2025/04/27 21:52:07 by yulpark          ###   ########.fr       */
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

static t_exec_error	create_pipe_n_fork(int *fd, pid_t *pid, t_command *cmd)
{
	int		check;

	if (cmd->is_pipe_next == true)
	{
		check = pipe(fd);
		if (check == -1)
			return (error_msg("failed to create a pipe.\n"), ERROR);
	}
	*pid = fork();
	if (*pid == -1)
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
	int		fd[2];
	int		i;
	pid_t	pid[data->nbr_of_cmds];

	i = 0;
	while (cmd != NULL)
	{
		if (create_pipe_n_fork(fd, &pid[i], cmd) != SUCCEED)
			return (ERROR);
		if (pid[i] == 0)
			cmd_executor(data, cmd, fd);
		close_parent_heredoc_fd(cmd->redir_list);
		if (data->last_fd_in != STDIN_FILENO)
			close(data->last_fd_in);
		if (cmd->is_pipe_next == true)
		{
			data->last_fd_in = fd[0];
			close(fd[1]);
		}
		cmd = cmd->next;
		i++;
	}
	wait_all_children(data, pid);
	return (SUCCEED);
}

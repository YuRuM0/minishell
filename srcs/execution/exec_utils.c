/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:23:29 by flima             #+#    #+#             */
/*   Updated: 2025/04/29 16:52:06 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_exec_error	redir_out(t_command *cmd, t_redir *outfile, int *fd)
{
	if (outfile != NULL)
	{
		if (dup2(outfile->fd, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (ERROR);
		}
	}
	else if (cmd->is_pipe_next == true)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (ERROR);
		}
	}
	return (SUCCEED);
}

static t_exec_error	redir_in(t_command *cmd, t_redir *infile, \
	t_redir *outfile, int *fd)
{
	t_exec_error	status;

	status = SUCCEED;
	if (infile != NULL)
	{
		if (dup2(infile->fd, STDIN_FILENO) == -1)
		{
			perror("minishell");
			status = ERROR;
		}
	}
	else if (cmd->data->last_fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->data->last_fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell");
			status = ERROR;
		}
	}
	if (status == SUCCEED)
		status = redir_out(cmd, outfile, fd);
	return (status);
}

t_exec_error	handle_files_n_redir(t_main_data *data, t_command *cmd, int *fd)
{
	if (setup_file_descriptors(cmd, data) != SUCCESS)
		return (ERROR);
	if (redir_in(cmd, cmd->infile, cmd->outfile, fd) != SUCCEED)
		return (ERROR);
	return (SUCCEED);
}

void	close_parent_heredoc_fd(t_redir *redir_list)
{
	while (redir_list != NULL)
	{
		if (redir_list && redir_list->redir_id == REDIR_HEREDOC)
			close(redir_list->fd);
		redir_list = redir_list->next;
	}
}

t_exec_error	close_fds_child(t_command *cmd)
{
	int	prev_errno;

	prev_errno = errno;
	errno = 0;
	if (cmd->infile != NULL && cmd->infile->fd > 0)
		close(cmd->infile->fd);
	if (cmd->outfile != NULL && cmd->outfile->fd > 0)
		close(cmd->outfile->fd);
	if (cmd->fd[0] != -2 && cmd->fd[1] != -2)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	if (cmd->data->last_fd_in != STDIN_FILENO)
		close(cmd->data->last_fd_in);
	if (errno != 0 && prev_errno == 0)
	{
		perror("minishell");
		return (ERROR);
	}
	return (SUCCEED);
}

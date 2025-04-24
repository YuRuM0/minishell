/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:04:08 by flima             #+#    #+#             */
/*   Updated: 2025/04/24 18:26:01 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//identificar se os comandos tem um input file e redirecionar o STDIN para ele
// se nao, usar o STDIN
// identificar se ha pipe e redirecionar para o pipe, se nao houver file in
//identificar o ultimo cmd e redirecionar para stdout ou um out file

static t_exec_error	redir_out(t_command *cmd, t_redir *outfile, int *fd)
{
	if (outfile != NULL)
	{
		if (dup2(outfile->fd, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			close(outfile->fd);
			return (ERROR);
		}
		close(outfile->fd);
	}
	else if (cmd->is_pipe_next == true)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell");
			close(fd[1]);
			return (ERROR);
		}
		close(fd[1]);
	}
	return (SUCCEED);
}

static t_exec_error	redir_in(t_command *cmd, t_redir *infile, \
	t_redir *outfile, int *fd)
{
	if (infile != NULL)
	{
		if (dup2(infile->fd, STDIN_FILENO) == -1)
		{
			perror("minishell");
			close(infile->fd);
			return (ERROR);
		}
		close(infile->fd);
	}
	else if (cmd->data->last_fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->data->last_fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell");
			close(cmd->data->last_fd_in);
			return (ERROR);
		}
		close(cmd->data->last_fd_in);
	}
	if (redir_out(cmd, outfile, fd) != SUCCEED)
		return (ERROR);
	return (SUCCEED);
}

void	cmd_executor(t_main_data *data, t_command *cmd, int *fd)
{
	char	*path;
	int		flag;

	flag = CHILD;
	setup_signal_handlers(CMD_CHILD);
	if (setup_file_descriptors(cmd, data) != SUCCESS)
		clean_all_data_exit(data, EXIT_FAIL);
	if (redir_in(cmd, cmd->infile, cmd->outfile, fd) != SUCCEED)
		clean_all_data_exit(data, EXIT_FAIL);
	if (builtinchecker(cmd) == true)
		manage_builtins(cmd, data, flag);
	else
	{
		path = executable_path(data, cmd);
		if (!path)
		{
			error_msg("command not found\n");
			clean_all_data_exit(data, EXIT_CMD_NOT_FOUND);
		}
		execve(path, cmd->args, data->envp_array);
		perror("minishell");
		clean_all_data_exit(data, EXIT_FAIL);
	}
}

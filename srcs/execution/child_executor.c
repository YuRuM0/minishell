/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:04:08 by flima             #+#    #+#             */
/*   Updated: 2025/04/22 18:05:26 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//identificar se os comandos tem um input file e redirecionar o STDIN para ele
// se nao, usar o STDIN
// identificar se ha pipe e redirecionar para o pipe, se nao houver file in
//identificar o ultimo cmd e redirecionar para stdout ou um out file

static void redir_out(t_command *cmd, t_redir *outfile, int *fd)
{
	if (outfile != NULL)
	{
		if (dup2(outfile->fd, STDOUT_FILENO) == -1)
			perror("minishell");
		close(outfile->fd);
	}
	else if (cmd->is_pipe_next == true)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("minishell");
		close(fd[1]);
	}
}
static int redir_in(t_command *cmd, t_redir *infile,\
	t_redir *outfile, int *fd)
{
	if (infile != NULL)
	{
		if (dup2(infile->fd, STDIN_FILENO) == -1)
			perror("minishell");
		close(infile->fd);
	}
	else if (cmd->data->last_fd_in != STDIN_FILENO) //not first
	{
		if (dup2(cmd->data->last_fd_in, STDIN_FILENO) == -1)
			perror("minishell");
		close(cmd->data->last_fd_in);
	}
	close(cmd->data->last_fd_in);
	redir_out(cmd, outfile, fd);
	return (SUCCEED);
}

void	cmd_executor(t_main_data *data, t_command *cmd, int *fd)
{
	char *path;
	int flag;

	flag = CHILD;
	setup_signal_handlers(CMD_CHILD);
	setup_file_descriptors(cmd, data);
	redir_in(cmd, cmd->infile, cmd->outfile, fd);
	sleep(5);
	if (manage_builtins(cmd, data, flag) == true)
		clean_all_data_exit(data, EXIT_SUCCESS);
	else
	{
		path = executable_path(data, cmd);
		if (!path)
			error_msg("Couldn't find the path\n");
		execve(path, cmd->args, data->envp_array);
		perror("minishell");
		clean_all_data_exit(data, EXIT_FAIL);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:04:08 by flima             #+#    #+#             */
/*   Updated: 2025/04/28 15:28:42 by flima            ###   ########.fr       */
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
	close_fds_child(cmd);
	return (status);
}

static void	get_valid_path(t_main_data *data, t_command *cmd,\
	 char **path)
{
	char	*msg;
	char	**env_path_var;
	int		i;

	env_path_var = NULL;
	i = 0;
	*path = executable_path(data, cmd, env_path_var, i);
	if (!*path)
	{
		if (data->exit_status == 0)
		{
			error_msg("command not found\n");
			clean_all_data_exit(data, EXIT_CMD_NOT_FOUND);
		}
		msg = ft_strjoin("minishell: ", cmd->args[0]);
		if (msg == NULL)
			status_error(data, ERROR_MEM_ALLOC);
		perror(msg);
		clean_all_data_exit(data, data->exit_status);
	}
}

static void remove_empty_cmds(t_command *cmd)
{
	int i = 0;
	char **args = cmd->args;

	if (args == NULL)
		return;

	while (args[i])
	{
		if (ft_strlen(args[i]) > 0)
			break;
		free(args[i]);
		i++;
	}
	if (args[i] == NULL)
		cmd->args = NULL;
	else
		cmd->args = &args[i];
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
	remove_empty_cmds(cmd);
	if (cmd->args == NULL)
		clean_all_data_exit(data, EXIT_SUCCESS);
	else
	{
		get_valid_path(data, cmd, &path);
		execve(path, cmd->args, data->envp_array);
		perror("minishell");
		clean_all_data_exit(data, EXIT_FAIL);
	}
}


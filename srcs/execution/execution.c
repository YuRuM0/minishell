/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:08:33 by flima             #+#    #+#             */
/*   Updated: 2025/04/21 16:28:22 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_exec_error redir_out_one_cmd(t_command *cmd, t_redir *outfile, int *saveout)
{
	if (cmd->outfile != NULL)
	{
		if (*saveout = dup(STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (ERROR);
		}
		if (dup2(cmd->outfile->fd, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			close(*saveout);
			close(cmd->outfile->fd);
			return (ERROR);
		}
		close(cmd->outfile->fd);
	}
	return (SUCCEED);
}
static t_exec_error redir_one_cmd(t_command *cmd, int *savein, int *saveout)
{
	*savein = -2;
	*saveout = -2;
	
	if (cmd->infile != NULL)
	{
		if (*savein = dup(STDIN_FILENO) == -1)
		{
			perror("minishell");
			return (ERROR);
		}
		if (dup2(cmd->infile->fd, STDIN_FILENO) == -1)
		{
			perror("minishell");
			close(*savein);
			close(cmd->infile->fd);
			return (ERROR);
		}
		close(cmd->infile->fd);
	}
	if (redir_out_one_cmd(cmd, cmd->outfile, saveout) != SUCCEED)
		return (close(*savein), ERROR);
	return (SUCCEED);
}

static void	reset_io_redirects(int	fd_in, int	fd_out)
{
	if (fd_in != -2)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

static t_exec_error	exec_one_cmd(t_command *cmd, t_main_data *data)
{
	char *path;
	int savein;
	int saveout;

	if (setup_file_descriptors(cmd, data) != SUCCESS)
		return (ERROR);
	if (redir_one_cmd(cmd, &savein, &saveout) != SUCCEED)
		return (ERROR);
	if (manage_builtins(cmd, data) == false)
	{
		path = executable_path(data, cmd);
		if (!path)
			error_msg("Couldn't find the path\n");
		else
		{
			if (path != NULL)
				execve(path, cmd->args, data->envp_array);
			perror("minishell");
			clean_all_data_exit(data, EXIT_FAIL);
		}
	
	}
	return (SUCCEED);
}


void	execution(t_main_data *data, t_command *cmd)
{
	if (data->nbr_of_cmds == 1)
		exec_one_cmd(cmd, data);
	else
	{
		//set_signals
		execute_pipeline(data, cmd);
	}
}

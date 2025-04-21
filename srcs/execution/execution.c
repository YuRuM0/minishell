/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:08:33 by flima             #+#    #+#             */
/*   Updated: 2025/04/21 23:04:46 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_exec_error redir_out_one_cmd(t_command *cmd, t_redir *outfile, int *saveout)
{
	if (outfile != NULL)
	{
		*saveout = dup(STDOUT_FILENO);
		if (*saveout == -1)
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
		*savein = dup(STDIN_FILENO);
		if (*savein == -1)
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

static t_exec_error	reset_io_redirects(int	fd_in, int	fd_out)
{
	if (fd_in != -2)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell");
			close(fd_in);
			return (ERROR);
		}
		close(fd_in);
	}
	if (fd_out != -2)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			close(fd_out);
			return(ERROR);
		}
		close(fd_out);
	}
	return (SUCCEED);
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
				execve(path, cmd->args, data->envp_array); //cant call execve in parent
			perror("minishell");
			clean_all_data_exit(data, EXIT_FAIL);
		}
	}
	if (reset_io_redirects(savein, saveout) != SUCCEED)
		return (ERROR);
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

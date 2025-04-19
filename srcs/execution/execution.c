/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:08:33 by flima             #+#    #+#             */
/*   Updated: 2025/04/19 20:00:33 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void redir_one_cmd(t_command *cmd, int *savein, int *saveout)
{
	*savein = -2;
	*saveout = -2;

	if (cmd->infile != NULL)
	{
		*savein = dup(STDIN_FILENO);
		if (dup2(cmd->infile->fd, STDIN_FILENO) == -1)
		{
			perror("minishell");
			close(cmd->infile->fd);
			return ;
		}
		close(cmd->infile->fd);
	}
	if (cmd->outfile != NULL)
	{
		*saveout = dup(STDOUT_FILENO);
		if (dup2(cmd->outfile->fd, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			close(cmd->outfile->fd);
			return ;
		}
		close(cmd->outfile->fd);
	}
}

static void	exec_one_cmd(t_command *cmd, t_main_data *data)
{
	char *path;
	int savein;
	int saveout;

	setup_file_descriptors(cmd, data);
	redir_one_cmd(cmd, &savein, &saveout);
	if (manage_builtins(cmd, data) == false)
	{
		path = executable_path(data, cmd);
		printf("%s\n", path);
		if (!path)
			error_msg("Couldn't find the path\n");
		else
		{
			if (execve(path, cmd->args, data->envp_array) != 0)
			{
				perror("minishell");
				//printf("HERE!\n");
				clean_all_data_exit(data, EXIT_FAIL);
			}
		}
	}
	if (savein != -2)
	{
		dup2(savein, STDIN_FILENO);
		close(savein);
	}
	if (saveout != -2)
	{
		dup2(saveout, STDOUT_FILENO);
		close(saveout);
	}
}


static void	wait_all_children(t_main_data *data, pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nbr_of_cmds)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
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

void	execution(t_main_data *data, t_command *cmd)
{
	int	fd[2];
	int	i;
	pid_t	pid[data->nbr_of_cmds];

	i = 0;
	if (data->nbr_of_cmds == 1)
		exec_one_cmd(cmd, data);
	else
	{
		//set_signals
		while (cmd != NULL)
		{
			pid[i] = create_pipe_n_fork(fd);
			if (pid[i] == ERROR)
				return ; // msg of error (perror)
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
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:04:08 by flima             #+#    #+#             */
/*   Updated: 2025/04/29 16:10:37 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_path_from_left(t_command *cmd, char **env_path_var)
{
	char	*path;
	int		i;

	i = 0;
	while (env_path_var[i])
	{
		path = ft_strputjoin(env_path_var[i], cmd->args[0], '/');
		if (path == NULL)
			break ;
		if (access(path, X_OK | F_OK) == 0)
		{
			free_double(env_path_var);
			return (path);
		}
		free(path);
		i++;
	}
	free_double(env_path_var);
	if (path == NULL && errno == ENOMEM)
		status_error(cmd->data, ERROR_MEM_ALLOC);
	return (NULL);
}

static void	get_valid_path(t_main_data *data, t_command *cmd, \
	char **path)
{
	char	*msg;
	char	**env_path_var;

	env_path_var = NULL;
	*path = executable_path(data, cmd, env_path_var);
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

static void	remove_empty_cmds(t_command *cmd)
{
	int		i;
	char	**args;

	i = 0;
	args = cmd->args;
	if (args == NULL)
		return ;
	while (args[i])
	{
		if (ft_strlen(args[i]) > 0)
			break ;
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
	if (handle_files_n_redir(data, cmd, fd) != SUCCEED)
	{
		close_fds_child(cmd);
		clean_all_data_exit(data, EXIT_FAIL);
	}
	if (close_fds_child(cmd) != SUCCEED)
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

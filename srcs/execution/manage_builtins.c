/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:05:00 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/29 16:45:44 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// if there is a command -> send the command to manage_builtins

//change to return the values from each builtins

t_exec_error	manage_builtins(t_command *cmd, t_main_data *data, int flag)
{
	t_exec_error	status;

	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
	{
		echo(cmd->args);
		status = SUCCEED;
	}
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		status = cd(cmd->args, data);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		status = env(data, cmd->args);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		status = ft_exit(cmd->args, data);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		status = export(cmd->args, data);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		status = pwd();
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		status = ft_unset(cmd->args, &data->env_vars);
	if (flag == CHILD)
		return (clean_all_data_exit(data, status), status);
	else
		return (status);
}

bool	builtinchecker(t_command *cmd)
{
	if (cmd->args[0] && cmd->args[0][0] == '\0')
		return (false);
	if (ft_strlen(cmd->args[0]) == 0)
		return (false);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (true);
	else
		return (false);
}

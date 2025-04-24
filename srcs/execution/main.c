/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:05:00 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/24 17:42:21 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// if there is a command -> send the command to manage_builtins

//change to return the values from each builtins
t_exec_error	manage_builtins(t_command *cmd, t_main_data *data, int flag)
{
	t_exec_error	status;

	status = SUCCEED;
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) == 0)
	{
		echo(cmd->args);
		status = SUCCEED;
	}
	else if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
		status = cd(cmd->args, data);
	else if (ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) == 0)
		status = env(data, cmd->args);
	else if (ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])) == 0)
		ft_exit(cmd->args, data);
	else if (ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) == 0)
		status = export(cmd->args, data);
	else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
		status = pwd(data);
	else if (ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])) == 0)
		status = ft_unset(cmd->args, &data->env_vars);
	if (flag == 2)
		return (clean_all_data_exit(data, status), status);
	else
		return (status);
}

bool	builtinchecker(t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])) == 0)
		return (true);
	else
		return (false);
}

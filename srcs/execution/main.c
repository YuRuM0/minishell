/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:05:00 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/19 16:29:33 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// if there is a command -> send the command to manage_builtins

//change to return the values from each builtins
bool	manage_builtins(t_command *cmd, t_main_data *data)
 {
 	if (ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) == 0)
 		echo(cmd->args);
 	else if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
 		ft_cd(cmd->args, data);
 	else if (ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) == 0)
 		env(data, cmd->args);
 	else if (ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])) == 0)
 		ft_exit(cmd->args, data);
 	else if (ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) == 0)
 		export(cmd->args, data);
 	else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
 		pwd(data);
 	else if (ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])) == 0)
 		ft_unset(cmd->args, &data->env_vars);
 	else
 		return (false);
 	return (true);
 }

// int	distribution(t_main_data *data)
// {
// 	char	*path;
// 	t_exec_error	res;

// 	if (data->nbr_of_cmds > 1)
// 	{
// 		if (manage_builtins(data) == true)
// 			return 0; //check if func from system
// 		path = executable_path(data);
// 		res = execute_one(path, data);
// 		if (path)
// 			free (path);
// 		return (res);
// 	}
// 	else if (pipecounter(data->pipeline))

// 	// update $?
// 	return (0);
// }

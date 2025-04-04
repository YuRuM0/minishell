/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:34:12 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/04 19:41:50 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	manage_builtins(char **args, t_env_var *envp, t_address add_list, t_main_data *data)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		echo(args, envp);
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		ft_cd(&args, add_list);
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		env(envp, args);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		ft_exit(&args, data);
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		export(args, envp, 1);
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		pwd();
	else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		fd_unset(args, envp);
	else
		write(1, "Not a builtin\n", 15);
}

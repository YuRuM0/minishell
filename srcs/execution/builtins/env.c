/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:50:32 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/04 18:40:06 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
// if env: display env variables
// if env VAR=value command (e.g ls): run a command with a temporary environment variable setting.

int	env(t_env_var *envp, char **args)
{
	int	i;
	if (!args[1])
	{
		while (envp)
		{
			i = 0;
			while (envp->variable[i])
			{
				write(1, &envp->variable[i], 1);
				i++;
			}
			envp = envp->next;
		}
		return (0);
	}
	else
		return(perror("Env: Wrong input"), -1);
}

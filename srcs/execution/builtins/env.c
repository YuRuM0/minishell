/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:50:32 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/07 16:53:44 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
// if env: display env variables

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
				if (envp->is_exported == 1)
					write(1, &envp->variable[i], 1);
				i++;
			}
			write(1, "\n", 1);
			envp = envp->next;
		}
		return (0);
	}
	else
	{
		write(1, "Env: env in this shell does not expect an argument\n", 52);
		return (-1);
	}
}

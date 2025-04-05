/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:50:32 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/05 18:37:16 by yulpark          ###   ########.fr       */
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
				write(1, &envp->variable[i], 1);
				i++;
			}
			write(1, "\n", 1);
			envp = envp->next;
		}
		return (0);
	}
	else
		return(perror("Env: env in this shell does not expect an argument\n"), -1);
}

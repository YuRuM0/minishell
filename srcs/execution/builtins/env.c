/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:50:32 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/25 21:28:45 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
// if env: display env variables

t_exec_error	env(t_main_data *data, char **args)
{
	int			i;
	t_env_var	*temp;

	temp = data->env_vars;
	if (!args[1])
	{
		while (temp)
		{
			i = 0;
			if (temp->is_exported == 1)
			{
				while (temp->variable[i])
				{
					write(1, &temp->variable[i], 1);
					i++;
				}
				write(1, "\n", 1);
			}
			temp = temp->next;
		}
	}
	else
		return (error_msg("Env: no argument expected\n")\
		, ERROR);
	return (SUCCEED);
}

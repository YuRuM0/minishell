/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:29:38 by flima             #+#    #+#             */
/*   Updated: 2025/03/28 21:20:31 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"


void	duplicate_env_var(t_main_data *data, char **env)
{
	int			i;
	t_env_var	*new_node;

	i = -1;
	while (env[++i])
	{
		new_node = add_new_var();
		if (new_node == NULL)
			status_error(data, ERROR_MEM_ALLOC);
		new_node->variable = env[i];
		add_var_back(&data->env_vars, new_node);
	}
	// print_en_var(data->env_vars);
	return (SUCCESS);
}



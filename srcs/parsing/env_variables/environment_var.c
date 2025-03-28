/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:29:38 by flima             #+#    #+#             */
/*   Updated: 2025/03/28 21:55:19 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"


void	duplicate_env_var(t_main_data *data, char **envp)
{
	int			i;
	t_env_var	*new_node;

	i = -1;
	while (envp[++i])
	{
		new_node = add_new_var();
		if (new_node == NULL)
			status_error(data, ERROR_MEM_ALLOC);
		new_node->variable = ft_strdup(envp[i]);
		if (new_node == NULL)
			status_error(data, ERROR_MEM_ALLOC);
		add_var_back(&data->env_vars, new_node);
	}
}

char	*find_environment_var(t_main_data *data, t_env_var *envp, \
	const char *var_name)
{
	int		i;
	size_t	len;
	char	*variable;
	
	i = -1;
	variable = NULL;
	len = ft_strlen(var_name);
	while (envp)
	{
		if ((ft_strncmp(envp->variable, var_name, len)) == 0)
		{
			variable = ft_strdup(envp->variable);
			if (variable == NULL)
				status_error(data, ERROR_MEM_ALLOC);
			break;
		}
		envp = envp->next;
	}
	return (variable);
}

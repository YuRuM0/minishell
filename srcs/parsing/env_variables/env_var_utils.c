/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:54:50 by flima             #+#    #+#             */
/*   Updated: 2025/04/08 16:22:20 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_env_var	*add_new_var(void)
{
	t_env_var	*node;

	node = ft_calloc(1, sizeof(t_env_var));
	if (node == NULL)
		return (NULL);
	node->variable = NULL;
	node->is_exported = 1;
	node->next = NULL;
	return (node);
}

void	add_var_back(t_env_var **head, t_env_var *new)
{
	t_env_var	*temp;

	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

static void	creat_exit_status_var(t_main_data *data)
{
	t_env_var	*exit_var;
	t_env_var	*tmp;
	
	exit_var = add_new_var();
	if (exit_var == NULL)
		status_error(data, ERROR_MEM_ALLOC);
	exit_var->variable = ft_strdup("?=0");
	if (exit_var->variable == NULL)
	{
		free(exit_var);
		status_error(data, ERROR_MEM_ALLOC);
	}
	exit_var->is_exported = 2;
	tmp = data->env_vars;
	data->env_vars = exit_var;
	exit_var->next = tmp;
}

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
		if (new_node->variable == NULL)
		{
			free(new_node);
			status_error(data, ERROR_MEM_ALLOC);
		}
		add_var_back(&data->env_vars, new_node);
	}
	creat_exit_status_var(data);
}

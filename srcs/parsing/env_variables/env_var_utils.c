/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:54:50 by flima             #+#    #+#             */
/*   Updated: 2025/03/30 16:22:57 by filipe           ###   ########.fr       */
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

char	*find_environment_var(t_main_data *data, char *var_name)
{
	size_t		len;
	t_env_var	*current;
	char 		*environ_var;
	
	current = data->env_vars;
	environ_var = NULL;
	len = ft_strlen(var_name);
	while (current)
	{
		if ((ft_strncmp(current->variable, var_name, len)) == 0)
		{
			environ_var = ft_strdup(current->variable);
			break;
		}
		current = current->next;
	}
	if (environ_var == NULL)
		environ_var = ft_strdup("");
	return (environ_var);
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
		if (new_node == NULL)
		{
			free(new_node);
			status_error(data, ERROR_MEM_ALLOC);
		}
		add_var_back(&data->env_vars, new_node);
	}
}

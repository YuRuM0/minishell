/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:54:50 by flima             #+#    #+#             */
/*   Updated: 2025/03/28 19:00:22 by flima            ###   ########.fr       */
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

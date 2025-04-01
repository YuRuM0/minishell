/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:04 by flima             #+#    #+#             */
/*   Updated: 2025/04/01 16:26:27 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_command	*add_new_cmd(void)
{
	t_command	*node;

	node = ft_calloc(1, sizeof(t_command));
	if (node == NULL)
		return (NULL);
	node->args = NULL;
	node->redir_list = NULL;
	node->is_builtin = false;
	node->is_pipe_next = false;
	node->next = NULL;
	return (node);
}

void	add_cmd_back(t_command **head, t_command *new)
{
	t_command	*temp;

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

t_redir	*add_new_redir(void)
{
	t_redir	*node;

	node = ft_calloc(1, sizeof(t_redir));
	if (node == NULL)
		return (NULL);
	node->redir_id = -1;
	node->fd = -1;
	node->file = NULL;
	node->next = NULL;
	return (node);
}

void	add_redir_back(t_redir **head, t_redir *new)
{
	t_redir	*temp;

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
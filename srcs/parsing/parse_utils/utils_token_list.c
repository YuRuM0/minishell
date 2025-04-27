/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:18:40 by flima             #+#    #+#             */
/*   Updated: 2025/04/27 21:14:20 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_token	*add_new_token(void)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->value = NULL;
	node->type = -1;
	node->next = NULL;
	return (node);
}

void	add_token_back(t_token **head, t_token *new)
{
	t_token	*temp;

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

t_token	*last_token(t_token *list)
{
	t_token	*last;

	if (!list)
		return (NULL);
	last = list;
	while (last->next)
		last = last->next;
	return (last);
}

void	remove_next_token(t_token *current)
{
	t_token	*tmp_token;

	tmp_token = current->next;
	current->next = current->next->next;
	tmp_token->next = NULL;
	free_tokens(tmp_token);
}
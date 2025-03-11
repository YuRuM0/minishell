/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:18:40 by flima             #+#    #+#             */
/*   Updated: 2025/03/11 16:30:30 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

/**
 * @brief Creates a new token.
 *
 * This function allocates memory for a new token of type `t_token` and 
 * initializes its fields. The `id` is set to -1, `str` is set to NULL, 
 * and `next` is initialized to NULL.
 *
 * @return A pointer to the newly created token, or NULL if memory 
 *         allocation fails.
 */
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

/**
 * @brief Adds a token to the end of a linked list of tokens.
 *
 * This function adds a new token to the end of the linked list. If the 
 * list is empty, it sets the new token as the head of the list.
 *
 * @param head Pointer to a pointer to the head of the token list. 
 *              The head of the list will be updated if it's currently NULL.
 * @param new Pointer to the new token to be added.
 */
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

/**
 * @brief Retrieves the last token in a linked list of tokens.
 *
 * This function traverses the linked list of tokens until it finds the 
 * last token (the one that has a NULL next pointer). If the list is empty, 
 * it returns NULL.
 *
 * @param list Pointer to the head of the token list.
 * @return Pointer to the last token in the list, or NULL if the list 
 *         is empty.
 */

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


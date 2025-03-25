/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:45:28 by flima             #+#    #+#             */
/*   Updated: 2025/03/24 18:30:52 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

// merge_adjacent_tokens like enviroment variables $
// and double quotes and single.
//

static void	remove_blank_tokens(t_token **current)
{
	t_token	*tmp;

	while (*current != NULL)
	{
		if ((*current)->type == NEW_LINE || \
			(*current)->type == TAB_CHAR || \
			(*current)->type == SPACE_CHAR)
		{
			tmp = *current;
			*current = (*current)->next;
			tmp->next = NULL;
			free_tokens(tmp);
		}
		else
			current = &(*current)->next;
	}
}

static void	remove_next_token(t_token *current)
{
	t_token	*tmp_token;

	tmp_token = current->next;
	current->next = current->next->next;
	tmp_token->next = NULL;
	free_tokens(tmp_token);
}

static t_pars_err	merge_quotes(t_token *current)
{
	char	*tmp_str;

	while (current->next && (current->next->type == D_QUOTE || \
			current->next->type == S_QUOTE || \
			current->next->type == WORD))
	{
		tmp_str = current->value;
		current->value = ft_strjoin(tmp_str, current->next->value);
		if (current == NULL && errno == ENOMEM)
			return (ERROR_MEM_ALLOC);
		free(tmp_str);
		remove_next_token(current);
	}
	return (SUCCESS);
}

static t_pars_err	merge_env_var(t_token *current)
{
	char	*tmp_str;

	if (!current->next || (ft_strlen(current->value) == 1 \
			&& current->next && \
			(current->next->type == TAB_CHAR || \
			current->next->type == NEW_LINE || \
			current->next->type == SPACE_CHAR)))
		current->type = WORD;
	else if (current->next && current->next->type == WORD)
	{
		tmp_str = current->value;
		current->value = ft_strjoin(tmp_str, current->next->value);
		if (current == NULL && errno == ENOMEM)
			return (ERROR_MEM_ALLOC);
		free(tmp_str);
		remove_next_token(current);
	}
	return (SUCCESS);
}

t_pars_err	merge_tokens_n_rm_blank_tokens(t_main_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current != NULL)
	{
		if (current->type == D_QUOTE || \
			current->type == S_QUOTE || \
			current->type == WORD)
		{
			if (merge_quotes(current) != SUCCESS)
				return (ERROR_MEM_ALLOC);
		}
		else if (current->type == VARIABLE)
		{
			if (merge_env_var(current) != SUCCESS)
				return (ERROR_MEM_ALLOC);
		}
		current = current->next;
	}
	remove_blank_tokens(&data->tokens);
	return (SUCCESS);
}

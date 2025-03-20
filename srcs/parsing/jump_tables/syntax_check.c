/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:34:46 by flima             #+#    #+#             */
/*   Updated: 2025/03/20 18:14:58 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_pars_err	syntax_pipe(t_token *previous, t_token *current)
{
	t_token	*next_token;

	if (previous == NULL)
		return (ERROR_UNEXPEC_PIPE);
	next_token = skip_blank_nodes_n_get_next(current, 0);
	if (next_token == NULL)
		return (ERROR_PIPE_END);
	if (next_token->type == PIPE)
		return (ERROR_UNEXPEC_PIPE);
	if (next_token->type == WORD && \
		(ft_strchr(next_token->value, '(') || \
		ft_strchr(next_token->value, ')')))
		return (ERROR_UNEXPEC_PARENTH);
	return (SUCCESS);
}

t_pars_err	syntax_great(t_token *previous, t_token *current)
{
	t_token	*next_token;

	(void)previous;
	next_token = skip_blank_nodes_n_get_next(current, 0);
	if (next_token == NULL)
		return (ERROR_MTCH_END);
	if (next_token->type == GREAT)
		return (ERROR_UNEXPEC_GREAT);
	if (next_token->type == LESS)
		return (ERROR_UNEXPEC_LESS);
	if (next_token->type == APPEND)
		return (ERROR_UNEXPEC_APPEND);
	if (next_token->type == HEREDOC)
		return (ERROR_UNEXPEC_HERDOC);
	if (next_token->type == PIPE)
		return (ERROR_UNEXPEC_PIPE);
	if (next_token->type == WORD && \
		(ft_strchr(next_token->value, '(') || \
		ft_strchr(next_token->value, ')')))
		return (ERROR_UNEXPEC_PARENTH);
	return (SUCCESS);
}

t_pars_err	syntax_append(t_token *previous, t_token *current)
{
	t_token	*next_token;

	(void)previous;
	next_token = skip_blank_nodes_n_get_next(current, 0);
	if (next_token == NULL)
		return (ERROR_MTCH_END);
	if (next_token->type == LESS)
		return (ERROR_UNEXPEC_LESS);
	if (next_token->type == GREAT)
		return (ERROR_UNEXPEC_GREAT);
	if (next_token->type == APPEND)
		return (ERROR_UNEXPEC_APPEND);
	if (next_token->type == HEREDOC)
		return (ERROR_UNEXPEC_HERDOC);
	if (next_token->type == PIPE)
		return (ERROR_UNEXPEC_PIPE);
	if (next_token->type == WORD && \
		(ft_strchr(next_token->value, '(') || \
		ft_strchr(next_token->value, ')')))
		return (ERROR_UNEXPEC_PARENTH);
	return (SUCCESS);
}

t_pars_err	syntax_less(t_token *previous, t_token *current)
{
	t_token	*next_token;

	(void)previous;
	next_token = skip_blank_nodes_n_get_next(current, 0);
	if (next_token == NULL)
		return (ERROR_MTCH_END);
	if (next_token->type == GREAT)
		return (ERROR_UNEXPEC_GREAT);
	if (next_token->type == LESS)
		return (ERROR_UNEXPEC_LESS);
	if (next_token->type == APPEND)
		return (ERROR_UNEXPEC_APPEND);
	if (next_token->type == HEREDOC)
		return (ERROR_UNEXPEC_HERDOC);
	if (next_token->type == PIPE)
		return (ERROR_UNEXPEC_PIPE);
	if (next_token->type == WORD && \
		(ft_strchr(next_token->value, '(') || \
		ft_strchr(next_token->value, ')')))
		return (ERROR_UNEXPEC_PARENTH);
	return (SUCCESS);
}

t_pars_err	syntax_heredoc(t_token *previous, t_token *current)
{
	t_token	*next_token;

	(void)previous;
	next_token = skip_blank_nodes_n_get_next(current, 0);
	if (next_token == NULL)
		return (ERROR_MTCH_END);
	if (next_token->type == LESS)
		return (ERROR_HERE_STR);
	if (next_token->type == GREAT)
		return (ERROR_UNEXPEC_GREAT);
	if (next_token->type == APPEND)
		return (ERROR_UNEXPEC_APPEND);
	if (next_token->type == HEREDOC)
		return (ERROR_HERE_STR);
	if (next_token->type == PIPE)
		return (ERROR_UNEXPEC_PIPE);
	if (next_token->type == WORD && \
		(ft_strchr(next_token->value, '(') || \
		ft_strchr(next_token->value, ')')))
		return (ERROR_UNEXPEC_PARENTH);
	return (SUCCESS);
}

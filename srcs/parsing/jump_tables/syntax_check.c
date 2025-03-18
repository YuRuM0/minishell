/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:34:46 by flima             #+#    #+#             */
/*   Updated: 2025/03/18 16:34:14 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_pars_err	syntax_pipe(t_token *previous, t_token *current)
{
	t_token	*tmp;

	tmp = current->next;
	if (previous == NULL)
		return (ERROR_UNEXPEC_PIPE);
	tmp = skip_blank_nodes_n_get_next(tmp, 1);
	if (tmp == NULL)
		return(ERROR_PIPE_END);
	if (current->next != NULL && current->next->type == PIPE)
		return(ERROR_UNEXPEC_PIPE);
	return (SUCCESS);
}

t_pars_err	syntax_great(t_token *previous, t_token *current)
{
	t_token	*tmp;
	
	(void)previous;
	tmp = skip_blank_nodes_n_get_next(current, 0);
	if (tmp == NULL)
		return (ERROR_MTCH_END);
	if(current->next->type == LESS)
		return (ERROR_UNEXPEC_LESS);
	if (current->next->type == PIPE)
		return (ERROR_UNEXPEC_PIPE);
	return (SUCCESS);
}

t_pars_err	syntax_append(t_token *previous, t_token *current)
{
	t_token	*tmp;
	
	(void)previous;
	tmp = skip_blank_nodes_n_get_next(current, 0);
	if (tmp == NULL)
		return (ERROR_MTCH_END);
	if(current->next->type == LESS)
		return (ERROR_UNEXPEC_LESS);
	if(current->next->type == GREAT)
		return (ERROR_UNEXPEC_GREAT);
	if(current->next->type == APPEND)
		return (ERROR_UNEXPEC_APPEND);
	if(current->next->type == HEREDOC)
		return (ERROR_UNEXPEC_HERDOC);
	if (current->next->type == PIPE)
		return (ERROR_UNEXPEC_PIPE);
	return (SUCCESS);
}

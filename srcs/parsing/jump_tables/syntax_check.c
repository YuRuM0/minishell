/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:34:46 by flima             #+#    #+#             */
/*   Updated: 2025/03/17 19:58:02 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_pars_err	syntax_pipe(t_token *previous, t_token *current)
{
	t_token	*tmp;

	tmp = current->next;
	if (previous == NULL)
		return (ERROR_PIPE_BEGIN);
	tmp = skip_blank_nodes_n_get_next(tmp, 1);
	if (tmp == NULL)
		return(ERROR_PIPE_END);
	if (current->next != NULL && current->next->type == PIPE)
		return(ERROR_PIPE_DOUBLE);
	return (SUCCESS);
}

t_pars_err	syntax_great(t_token *previous, t_token *current)
{
	
}
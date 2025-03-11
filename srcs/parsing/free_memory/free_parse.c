/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:17:50 by flima             #+#    #+#             */
/*   Updated: 2025/03/11 18:28:50 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	
	while (*tokens != NULL)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp);
	}
}
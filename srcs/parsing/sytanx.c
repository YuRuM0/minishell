/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sytanx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:03:24 by flima             #+#    #+#             */
/*   Updated: 2025/03/14 18:32:23 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

// identify syntax erros in the tokens list
t_token	*skip_blank_nodes_n_get_next(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (NULL);
	current = tokens->next;
	while (current && current->type != SPACE_CHAR && \
		current->type != NEW_LINE && current->type != TAB_CHAR)
		current = current->next;
	return (current);
}

vstatic void	assign_syntax_func(t_syntax_check *table)
{
	table[0] = 
	table[1] = 
	table[2] = 
	table[3] = 
	table[4] = 
	table[5] = 
	table[6] = 
	table[7] = 
	table[8] =  
}
t_pars_err	syntax(t_main_data *data)
{
	t_token			*current;
	t_token			*previous;
	t_pars_err		status;
	t_syntax_check syntax_table[9];

	
	previous = NULL;
	current = data->tokens;
	assign_syntax_funcs(syntax_table);
	while (current != NULL)
	{
		//syntax_table function(previous, current);
		previous = current;
		current = skip_blank_nodes(current);
	}
}
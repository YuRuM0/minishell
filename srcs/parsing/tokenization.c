/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:18:11 by filipe            #+#    #+#             */
/*   Updated: 2025/02/23 17:05:27 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ercode_pars	get_tokens(char *input, int *i, t_token *token)
{
	
}

t_ercode_pars	tokenize_input(t_main_data *data, char	*input)
{
	t_token			*token;
	size_t			i;
	t_ercode_pars	status;

	i = 0;
	while(input[i])
	{
		token = add_new_token();
		if (!token)
			return (ERR_MEM_ALLOC);
		status = get_tokens(input, &i, token);
		//check err code in status 
		//if (status == ?)
		add_token_back(&data->tokens, token);
	}
	return(PARSE_SUCCESS);
}

t_ercode_pars	parser(t_main_data *data)
{
	t_ercode_pars	status;

	status = tokenize_input(data, data->pipeline);
	

	
}

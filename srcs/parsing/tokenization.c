/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:18:11 by filipe            #+#    #+#             */
/*   Updated: 2025/05/08 20:33:07 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

//jump table to the lexer functions 
static	void	assign_lex_funcs(t_lex_functions *process)
{
	process[0] = process_word_n_spaces;
	process[1] = process_word_n_spaces;
	process[2] = process_word_n_spaces;
	process[3] = process_pipe;
	process[4] = process_less_n_append;
	process[5] = process_great_n_herdoc;
	process[6] = process_env_var;
	process[7] = process_double_quotes;
	process[8] = process_single_quotes;
	process[9] = NULL;
	process[10] = process_word_n_spaces;
}

//identify the token type and return it.
t_syntax	get_token_type(char cha)
{
	t_syntax	type;

	type = SPACE_CHAR;
	while (type != WORD)
	{
		if (cha == METACHARS[type])
			return (type);
		type++;
	}
	return (WORD);
}

t_pars_err	assign_token(char *input, size_t *current_pos, t_token *token)
{
	t_lex_functions		process[11];
	t_pars_err			status;
	size_t				start;

	start = *current_pos;
	assign_lex_funcs(process);
	token->type = get_token_type(input[*current_pos]);
	if (token->type == AND)
		return (ERROR_AND_OPERATOR);
	status = process[token->type](input, current_pos, &token->type);
	if (status != SUCCESS)
		return (status);
	token->value = ft_substr(input, start, *current_pos - start);
	if (token->value == NULL)
		return (ERROR_MEM_ALLOC);
	return (SUCCESS);
}

t_pars_err	tokenize_input(t_main_data *data, char	*input)
{
	t_token			*token;
	size_t			i;
	t_pars_err		status;

	i = 0;
	while (input[i])
	{
		token = add_new_token();
		if (!token)
			return (ERROR_MEM_ALLOC);
		status = assign_token(input, &i, token);
		add_token_back(&data->tokens, token);
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}

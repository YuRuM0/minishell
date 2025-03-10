/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:44:47 by flima             #+#    #+#             */
/*   Updated: 2025/03/10 15:52:53 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// moves i true the input while tok_type is equal the current token type in input[i]
// returns a error code
t_pars_err	process_word_n_spaces(char *input, size_t *i, t_syntax *tok_type)
{
	while (input[*i] && get_token_type(input[*i]) == *tok_type)
		(*i)++;
	return(SUCCESS);
}

t_pars_err	process_pipe(char *input, size_t *i, t_syntax *tok_type)
{
	(void)tok_type;
	(*i)++;
	return (SUCCESS);
}

t_pars_err	process_great_n_herdoc(char *input, size_t *i, t_syntax *tok_type)
{
	if (input[*i + 1] == '<')
	{
		(*i)++;
		*tok_type = HEREDOC;
	}
	(*i)++;
	return (SUCCESS);
}

t_pars_err	process_less_n_append(char *input, size_t *i, t_syntax *tok_type)
{
	if (input[*i + 1] == '>')
	{
		(*i)++;
		*tok_type = APPEND;
	}
	(*i)++;
	return (SUCCESS);
}

t_pars_err	process_env_var(char *input, size_t *i, t_syntax *tok_type)
{
	(void)tok_type;
	(*i)++;
	while (input[*i] && get_token_type(input[*i]) == WORD)
		(*i)++;
	return(SUCCESS);
}
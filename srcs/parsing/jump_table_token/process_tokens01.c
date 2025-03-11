/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:44:47 by flima             #+#    #+#             */
/*   Updated: 2025/03/11 18:35:37 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

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
	(void)input;
	(*i)++;
	return (SUCCESS);
}

t_pars_err	process_great_n_herdoc(char *input, size_t *i, t_syntax *tok_type)
{
	if (input[*i + 1] == '>')
	{
		(*i)++;
		*tok_type = APPEND;
	}
	(*i)++;
	return (SUCCESS);
}

t_pars_err	process_less_n_append(char *input, size_t *i, t_syntax *tok_type)
{
	if (input[*i + 1] == '<')
	{
		(*i)++;
		*tok_type = HEREDOC;
	}
	(*i)++;
	return (SUCCESS);
}

// handle env_var, we dont handle command substitution $(CMD)
// we just handle special char ?
t_pars_err	process_env_var(char *input, size_t *i, t_syntax *tok_type)
{
	(void)tok_type;
	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (SUCCESS);
	}
	if (input[*i] == '(')
		return (ERROR_CMD_SUBSTITUTION);
	if (!ft_isalpha(input[*i] && input[*i] != '_'))
		return (SUCCESS);
	(*i)++;
	while (ft_isalnum(input[*i] || input[*i] == '_'))
		(*i)++;
	return(SUCCESS);
}

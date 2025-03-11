/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:51:47 by flima             #+#    #+#             */
/*   Updated: 2025/03/11 13:58:34 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// handle with \" and \'
// should I handle (cmd = echo "test)? bash: works like heredoc
// or should I handle it like an error?
t_pars_err	process_single_quotes(char *input, size_t *i, t_syntax *tok_type)
{
	(*i)++;
	while (input[*i] != '\'' && input[*i])
		(*i)++;
	if (input[*i] == '\0')
		return (UNCLOSED_QUOTE);
	(*i)++;
	return (SUCCESS);
}

t_pars_err	process_double_quotes(char *input, size_t *i, t_syntax *tok_type)
{
	(*i)++;
	while (input[*i] != '\"' && input[*i])
		(*i)++;
	if (input[*i] == '\0')
		return (UNCLOSED_QUOTE);
	(*i)++;
	return (SUCCESS);
}

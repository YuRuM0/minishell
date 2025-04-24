/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:49:35 by filipe            #+#    #+#             */
/*   Updated: 2025/04/24 19:34:08 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

static t_pars_err	trim_quotes(t_token *token)
{
	char	*tmp;

	tmp = token->value;
	if (token->type == D_QUOTE)
		tmp = ft_strtrim(tmp, "\"");
	else if (token->type == S_QUOTE)
		tmp = ft_strtrim(tmp, "\'");
	if (tmp == NULL)
		return (ERROR_MEM_ALLOC);
	free(token->value);
	token->value = tmp;
	return (SUCCESS);
}

static t_pars_err	expand_token(t_env_var *envp, t_token *token)
{
	t_pars_err	status;
	char		*var_value;

	if (token->type == WORD)
	{
		status = expand_environ_var(envp, &token->value, &var_value);
		if (status == ERROR_MEM_ALLOC)
			return (status);
		free(token->value);
		token->value = var_value;
		return (SUCCESS);
	}
	status = expand_env_instr(envp, &token->value);
	if (status == ERROR_MEM_ALLOC)
		return (ERROR_MEM_ALLOC);
	return (SUCCESS);
}

t_pars_err	expand_token_n_trim_quote(t_env_var *envp, t_token *token)
{
	t_pars_err	status;

	while (token != NULL)
	{
		if (token->type == D_QUOTE || token->type == S_QUOTE)
		{
			status = trim_quotes(token);
			if (status == ERROR_MEM_ALLOC)
				return (ERROR_MEM_ALLOC);
		}
		if (token->type == D_QUOTE || token->type == VARIABLE ||\
			(token->type == WORD && ft_strncmp(token->value, "~", 2) == 0))
		{
			status = expand_token(envp, token);
			if (status == ERROR_MEM_ALLOC)
				return (ERROR_MEM_ALLOC);
		}
		token = token->next;
	}
	return (SUCCESS);
}

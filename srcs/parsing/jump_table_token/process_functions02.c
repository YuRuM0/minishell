/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_functions02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:51:47 by flima             #+#    #+#             */
/*   Updated: 2025/03/10 17:57:26 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// handle with \" and \'
t_pars_err	process_quotes(char *input, size_t *i, t_syntax *tok_type)
{
	(*i)++;
	if (input[*i - 1] == '\'')
	{
		while (input[*i] != '\'' && input[*i])
			(*i)++;
	}
	
}
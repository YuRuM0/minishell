/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:49:49 by flima             #+#    #+#             */
/*   Updated: 2025/03/17 18:15:11 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	error_msg(char *msg)
{
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

void	assign_error_table_msg(char **table)
{
	table[0] = "minishell: syntax error near unexpected token 'newline'\n";
	table[1] = "minishell: syntax error near unexpected token '|'\n";
}

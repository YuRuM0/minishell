/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:49:49 by flima             #+#    #+#             */
/*   Updated: 2025/04/24 18:19:46 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	error_msg(char *msg)
{
	if (msg)
	{
		write(STDOUT_FILENO, "minishell: ", 12);
		write(STDOUT_FILENO, msg, ft_strlen(msg));
	}
	if (!msg && errno == ENOMEM)
	{
		perror("minishell");
		//set_terminal
		if (isatty(STDIN_FILENO))
			rl_clear_history();
	}
}

void	assign_error_table_msg(char **table)
{
	table[0] = "syntax error near unexpected token 'newline'\n";
	table[1] = "multiples lines command not suported\n";
	table[2] = "syntax error near unexpected token '|'\n";
	table[3] = "syntax error near unexpected token '<'\n";
	table[4] = "syntax error near unexpected token '>'\n";
	table[5] = "syntax error near unexpected token '>>'\n";
	table[6] = "syntax error near unexpected token '<<'\n";
	table[7] = "syntax error near unexpected token ')' or '('\n";
}

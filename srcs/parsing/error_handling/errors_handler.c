/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:16:47 by flima             #+#    #+#             */
/*   Updated: 2025/03/17 17:58:55 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	status_error_tokeniz(t_main_data *data, t_pars_err status)
{
	if (status == UNCLOSED_QUOTE)
		error_msg("minishell: syntax error: unclosed quotes\n");
	else if (status == ERROR_CMD_SUBSTITUTION)
	{
		error_msg("minishell: syntax error : arithmetic expansion or ");
		error_msg("command substitution not supported\n");
	}
	else
	{
		perror("minishell");
		clean_all_data_error(data, EXIT_MEM_FAILURE);
	}
}

void	status_error_syntax(t_main_data *data, t_pars_err status)
{
	char	*table[2];

	(void)data;
	assign_error_table_msg(table);
	if (status == ERROR_PIPE_DOUBLE || status == ERROR_PIPE_BEGIN)
		error_msg(table[1]);
	else if (status == ERROR_PIPE_END)
		error_msg(table[0]);
}

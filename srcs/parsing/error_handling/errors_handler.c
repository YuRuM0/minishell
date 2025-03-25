/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:16:47 by flima             #+#    #+#             */
/*   Updated: 2025/03/25 19:07:11 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	status_error(t_main_data *data, t_pars_err status)
{
	if (status == UNCLOSED_QUOTE)
		error_msg("syntax error: unclosed quotes\n");
	else if (status == ERROR_CMD_SUBSTITUTION)
		error_msg("arithmetic expansion or cmd substitution not supported\n");
	else if (status == ERROR_AND_OPERATOR)
		error_msg("logical AND or background operator not suported\n");
	else
	{
		perror("minishell");
		clean_all_data_exit(data, EXIT_MEM_FAILURE);
	}
}

void	status_error_syntax(t_main_data *data, t_pars_err status)
{
	char	*table[8];

	(void)data;
	assign_error_table_msg(table);
	error_msg(table[status - 5]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:16:47 by flima             #+#    #+#             */
/*   Updated: 2025/03/12 17:20:01 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	error_msg(char *msg)
{
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

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

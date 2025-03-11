/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:16:47 by flima             #+#    #+#             */
/*   Updated: 2025/03/11 20:14:50 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	error_msg(char *msg, int out_status)
{
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	exit(out_status);
}

static void	assign_err_table(t_handle_error *table)
{
	table[0] =
	table[1] = 
	table[2] = 
	table[3] = memory_error;
}
void	handle_status_error(t_main_data *data, t_pars_err status)
{
	t_handle_error	err_table[4];
	
	
}
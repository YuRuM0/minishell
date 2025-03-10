/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:16:47 by flima             #+#    #+#             */
/*   Updated: 2025/02/22 22:08:24 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg, int out_status)
{
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	exit(out_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:04:08 by flima             #+#    #+#             */
/*   Updated: 2025/04/15 19:21:51 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizat"

//identificar se os comandos tem um input file e redirecionar o STDIN para ele
// se nao, usar o STDIN
// identificar se ha pipe e redirecionar para o pipe, se nao houver file in
//identificar o ultimo cmd e redirecionar para stdout ou um out file
static redirection(t_redir	*redir, int current_cmd)
{
	
}
void	cmd_executor(t_main_data *data, t_command *cmd, int current_cmd)
{
	//redir 
	//close fds
	//execu
	//error msg
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:04:08 by flima             #+#    #+#             */
/*   Updated: 2025/04/18 21:33:56 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//identificar se os comandos tem um input file e redirecionar o STDIN para ele
// se nao, usar o STDIN
// identificar se ha pipe e redirecionar para o pipe, se nao houver file in
//identificar o ultimo cmd e redirecionar para stdout ou um out file

static redirection(t_command *simple_cmd, t_redir *infile,\
	t_redir *outfile, int current_cmd)
{
	simple_cmd->
	if (infile != NULL)
	{
		if (dup2(infile->fd, STDIN_FILENO) == -1)
			perror("minishell");
		
	}
	else if (last-in != STDIN_FILENO)
		dup2(last-in, STDIN_FILENO)
		close(last-In)


		
	if (outfile != NULL)
	{
		
	}
	else
	{
		if (simple_cmd->is_pipe_next == true)
			//dup pipe
	}
}
{
	
}
void	cmd_executor(t_main_data *data, t_command *cmd, int current_cmd)
{
	// check the path
	//redir 
	//close fds
	//execu
	//error msg
}
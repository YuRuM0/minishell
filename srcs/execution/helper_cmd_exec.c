/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:54:55 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/02 23:22:13 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
//redirec_hanlder
//func that reconstructs the cmd to follow the correct format

/*typedef struct s_redir
{
	t_redir_id		redir_id;
	int				fd;
	char			*file;
	struct s_redir 	*next;
}					t_redir;
*/

int iter_redir(t_command *cmd)
{
	t_redir *current;
	
	if (!cmd)
		return (-1);
	if (!cmd->args[0]) //args[0] holds the command? e.g. export?
		return (-1);
	current = cmd->redir_list;
	while (current)
	{
		//open
		//redirect
		// move on to the next one on the list
	}
	return (0);
}
// to read: https://www.gnu.org/software/bash/manual/html_node/Redirections.html
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:48:17 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/05 17:18:22 by yulpark          ###   ########.fr       */
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

/*t_command	*add_new_cmd(void)
{
	t_command	*node;

	node = ft_calloc(1, sizeof(t_command));
	if (node == NULL)
		return (NULL);
	node->args = NULL;
	node->redir_list = NULL;
	node->is_builtin = false;
	node->is_pipe_next = false;
	node->next = NULL;
	return (node);
}*/

int openfile(int fd, t_redir *redir, char *file)
{
	if (redir->redir_id == REDIR_IN)
		fd = open(file, O_RDONLY);
	else if (redir->redir_id == REDIR_OUT)
		fd = open(file, O_WRONLY); // either overwrite or create new
//	else if (ft_strncmp(redir_type, ">", 1) == 0)
//	// either delete current one or create new
//		fd = open(file, O_WRONLY);
//	else if (ft_strncmp(redir_type, ">>", 2) == 0)
//	//append or create
//		fd = open(file, O_WRONLY);
//	else if (ft_strncmp(redir_type, "HERE", 4) == 0) // temp file already open, only saving fd.
//	//error?
//	return (0);
}

//int redirect();

int iter_redir(t_command *cmd)
{
	t_redir *current;
	int result;

	if (!cmd)
		return (-1);
	if (!cmd->args[0]) //args[0] holds the command? e.g. export?
		return (-1);
	current = cmd->redir_list;
	while (current)
	{
		if (current->file)
		{
			result = openfile(current->fd, current->redir_id, current->file);
			if (result != 0)
				return (-1);
			redirect();
		}


		//redirect
		current = current->next;
	}
	return (0);
}
// to read: https://www.gnu.org/software/bash/manual/html_node/Redirections.html

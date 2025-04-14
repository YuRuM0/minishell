/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:48:17 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/11 18:25:01 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//redirec_hanlder
//func that reconstructs the cmd to follow the correct format

typedef struct s_redir
{
	t_redir_id		redir_id;
	int				fd;
	char			*file;
	struct s_redir 	*next;
}					t_redir;

t_command	*add_new_cmd(void)
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
}

//fd is not an int?
int openfile(t_redir *redir)
{
	if (!redir || !redir->file)
		return (-1);   // what happens to whatever is in the struct then?
	if (redir->redir_id == REDIR_IN)
		redir->fd = open(redir->file, O_RDONLY);
	else if (redir->redir_id == REDIR_OUT)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT, 0644);
	else if (redir->redir_id == REDIR_APPEND)
		redir->fd = open(redir->file, O_WRONLY | O_APPEND, 0644);
	else if (redir->redir_id == REDIR_HEREDOC)
		//redir->fd = //where is the temp file
	return (redir->fd);
}

//int redirect();

int iter_redir(t_command *cmd)
{
	t_redir *current;
	int result;

	if (!cmd)
		return (-1);
	if (!cmd->args[0])
		return (-1);
	current = cmd->redir_list;
	while (current)
	{
		if (current->file)
		{
			result = openfile(current);
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

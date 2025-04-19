/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:48:17 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/19 16:37:49 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "execution.h"
///*
////redirec_hanlder
////func that reconstructs the cmd to follow the correct format

//typedef struct s_redir
//{
//	t_redir_id		redir_id;
//	int				fd;
//	char			*file;
//	struct s_redir 	*next;
//}					t_redir;

//t_command	*add_new_cmd(void)
//{
//	t_command	*node;

//	node = ft_calloc(1, sizeof(t_command));
//	if (node == NULL)
//		return (NULL);
//	node->args = NULL;
//	node->redir_list = NULL;
//	node->is_builtin = false;
//	node->is_pipe_next = false;
//	node->next = NULL;
//	return (node);
//}
//*/
//int openfile(t_redir *redir)
//{
//	int	redir_fd;

//	if (!redir)
//		return (0);
//	if (redir->redir_id == REDIR_IN)
//		redir_fd = open(redir->file, O_RDONLY);
//	else if (redir->redir_id == REDIR_OUT)
//		redir_fd = open(redir->file, O_WRONLY | O_CREAT, 0644);
//	else if (redir->redir_id == REDIR_APPEND)
//		redir_fd = open(redir->file, O_WRONLY | O_APPEND, 0644);
//	else if (redir->redir_id == REDIR_HEREDOC)
//		redir_fd = ft_atoi(redir->file); //why
//	if (redir_fd == -1)
//		return (ERROR);
//	return (redir_fd);
//}

////t_exec_error	redir_ins(t_redir *redir, int redir_fd)
////{
////	if (redir->fd = STDIN_FILENO)
////		redir->fd = redir_fd;
////	else if (redir->fd == ERROR)
////	{
////		redir
////	}
////}

////t_exec_error redir_outs(t_redir *redir, int redir_fd)
////{
////	if (redir->fd = STDOUT_FILENO)
////}

//t_exec_error iter_redir(t_command *cmd)
//{
//	t_redir *current;
//	t_exec_error res;
//	int result;

//	if (!cmd || !cmd->args[0])
//		return (-1);
//	current = cmd->redir_list; //redir happens l->r
//	while (current)
//	{
//		if (current->file)
//		{
//			result = openfile(current);
//			if (result != 0)
//				return (ERROR);
//		}
//		if (cmd->redir_list->redir_id == REDIR_IN || cmd->redir_list->redir_id == REDIR_HEREDOC)
//			res = redir_ins(cmd->redir_list, result);
//		else
//			res = redir_outs(cmd->redir_list, result);
//		if (res == ERROR)
//			return (ERROR);
//		current = current->next;
//	}
//	return (SUCCEED);
//}

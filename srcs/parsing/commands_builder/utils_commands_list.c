/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:04 by flima             #+#    #+#             */
/*   Updated: 2025/04/28 14:54:56 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_command	*add_new_cmd(t_main_data *data)
{
	t_command	*node;

	node = ft_calloc(1, sizeof(t_command));
	if (node == NULL)
		return (NULL);
	node->args = NULL;
	node->redir_list = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->is_builtin = false;
	node->is_pipe_next = false;
	node->fd[0] = -2;
	node->fd[1] = -2;
	node->next = NULL;
	node->data = data;
	return (node);
}

void	add_cmd_back(t_command **head, t_command *new)
{
	t_command	*temp;

	if (new == NULL)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

t_redir	*add_new_redir(void)
{
	t_redir	*node;

	node = ft_calloc(1, sizeof(t_redir));
	if (node == NULL)
		return (NULL);
	node->redir_id = -1;
	node->fd = -2;
	node->file = NULL;
	node->next = NULL;
	return (node);
}

void	add_redir_back(t_redir **head, t_redir *new)
{
	t_redir	*temp;

	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

t_pars_err	init_cmd_args(t_command *cmd, t_token *current)
{
	int			size;
	char		**args;

	size = get_args_size(current);
	if (size >= 0)
	{
		args = malloc(sizeof(char *) * (size + 1));
		if (args == NULL)
			return (ERROR_MEM_ALLOC);
		args[size] = NULL;
		cmd->args = args;
	}
	return (SUCCESS);
}

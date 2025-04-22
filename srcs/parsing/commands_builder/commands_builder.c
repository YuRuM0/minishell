/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:44:02 by flima             #+#    #+#             */
/*   Updated: 2025/04/22 19:00:18 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	get_args_size(t_token *tokens)
{
	int	size;
	int	less;

	size = 0;
	less = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == HEREDOC || \
			tokens->type == APPEND \
			|| tokens->type == GREAT || \
			tokens->type == LESS)
		{
			size++;
			less++;
		}
		else
			size++;
		tokens = tokens->next;
	}
	size = size - (less * 2);
	return (size);
}

t_pars_err	assign_redir(t_command *cmd, t_token *current)
{
	t_redir	*new_redir;

	new_redir = add_new_redir();
	if (new_redir == NULL)
		return (ERROR_MEM_ALLOC);
	add_redir_back(&cmd->redir_list, new_redir);
	if (current->type == HEREDOC)
	{
		new_redir->redir_id = REDIR_HEREDOC;
		new_redir->fd = ft_atoi(current->next->value);
		return (SUCCESS);
	}
	else if (current->type == APPEND)
		new_redir->redir_id = REDIR_APPEND;
	else if (current->type == GREAT)
		new_redir->redir_id = REDIR_OUT;
	else if (current->type == LESS)
		new_redir->redir_id = REDIR_IN;
	new_redir->file = ft_strdup(current->next->value);
	// file name condition
	if (new_redir->file == NULL)
		return (ERROR_MEM_ALLOC);
	return (SUCCESS);
}

t_pars_err	assign_args(t_command *cmd, t_token *current, int *i)
{
	(cmd->args)[*i] = ft_strdup(current->value);
	if ((cmd->args)[*i] == NULL)
		return (ERROR_MEM_ALLOC);
	(*i)++;
	return (SUCCESS);
}

t_pars_err	append_token_in_cmd(t_command *cmd, t_token **current)
{
	int			i;

	i = 0;
	if (init_cmd_args(cmd, *current) != SUCCESS)
		return (ERROR_MEM_ALLOC);
	while (*current && (*current)->type != PIPE)
	{
		if ((*current)->type == HEREDOC || (*current)->type == APPEND \
			|| (*current)->type == GREAT || (*current)->type == LESS)
		{
			if (assign_redir(cmd, *current) != SUCCESS)
				return (ERROR_MEM_ALLOC);
			*current = (*current)->next->next;
		}
		else if ((*current)->type == WORD || (*current)->type == D_QUOTE \
			|| (*current)->type == S_QUOTE || (*current)->type == VARIABLE)
		{
			if (assign_args(cmd, *current, &i) != SUCCESS)
				return (ERROR_MEM_ALLOC);
			*current = (*current)->next;
		}
	}
	return (SUCCESS);
}

t_pars_err	commands_builder(t_main_data *data)
{
	t_command	*cmd;
	t_token		*token;

	cmd = add_new_cmd(data);
	if (cmd == NULL)
		return (ERROR_MEM_ALLOC);
	data->cmds = cmd;
	token = data->tokens;
	while (token != NULL)
	{
		data->nbr_of_cmds++;
		if (token->type == PIPE)
		{
			cmd->is_pipe_next = true;
			cmd = add_new_cmd(data);
			if (cmd == NULL)
				return (ERROR_MEM_ALLOC);
			add_cmd_back(&data->cmds, cmd);
			token = token->next;
		}
		if (append_token_in_cmd(cmd, &token) != SUCCESS)
			return (ERROR_MEM_ALLOC);
	}
	return (SUCCESS);
}

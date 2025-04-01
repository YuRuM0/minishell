/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:44:02 by flima             #+#    #+#             */
/*   Updated: 2025/04/01 18:55:41 by flima            ###   ########.fr       */
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
		if (tokens->type == HEREDOC || tokens->type == APPEND\
			|| tokens->type == GREAT || tokens->type == LESS)
		{
			size++;
			less++;
		}
		else
			size++;
		tokens = tokens->next;
	}
	size = size - less;
	return (size);
}
t_pars_err	assign_args(t_command *cmd, t_token *current)
{
	
}
t_pars_err	append_token_in_cmd(t_command *cmd, t_token *current)
{
	t_pars_err	status;
	
	if (current->type == WORD || current->type == D_QUOTE\
		|| current->type == S_QUOTE || current->type == VARIABLE)
	{
		status = assign_args(cmd, current);
	}
}
t_pars_err	commands_builder(t_main_data *data)
{
	t_command	*cmd;
	t_token		*token;

	cmd = add_new_cmd();
	if (cmd == NULL)
		return (ERROR_MEM_ALLOC);
	token = data->tokens;
	while (token != NULL)
	{
		if (token->type == PIPE)
		{
			cmd->is_pipe_next = true;
			cmd = add_new_cmd();
			if (cmd == NULL)
				return (ERROR_MEM_ALLOC);
		}
		append_token_in_cmd(cmd, token);
	}
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:17:50 by flima             #+#    #+#             */
/*   Updated: 2025/04/03 23:48:34 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_env_vars(t_env_var *head)
{
	t_env_var	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->variable);
		free(tmp);
	}
}

void free_cmds(t_command *cmds)
{
	t_redir		*tmp;
	t_command	*tmp_cmd;
	char		**args;

	while (cmds != NULL)
	{
		while (cmds->redir_list != NULL)
		{
			tmp = cmds->redir_list;
			cmds->redir_list = cmds->redir_list->next;
			free(tmp->fd);
			free(tmp->file);
			free(tmp);
		}
		tmp_cmd = cmds;
		cmds = cmds->next;
		args = tmp_cmd->args;
		while (args != NULL && *args != NULL)
		{
			free(*args);
			args++;
		}
		free(tmp_cmd->args);
		free(tmp_cmd);
	}
}
void	clean_temp_data(t_main_data *data)
{
	free_tokens(data->tokens);
	free_cmds(data->cmds);
	free(data->pipeline);
	data->cmds = NULL;
	data->pipeline = NULL;
	data->tokens = NULL;
}

void	clean_all_data_exit(t_main_data *data, int out_status)
{
	rl_clear_history();
	//set_terminal
	free_env_vars(data->env_vars);
	free_tokens(data->tokens);
	free_cmds(data->cmds);
	free(data->pipeline);
	exit(out_status);
}

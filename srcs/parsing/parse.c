/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:29:45 by filipe            #+#    #+#             */
/*   Updated: 2025/04/15 18:24:55 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "execution.h"

t_pars_err	parser(t_main_data *data)
{
	t_pars_err	status;

	if (data->pipeline == NULL)
		return (SUCCESS);
	if (*(data->pipeline) == '\0')
		return (SUCCESS);
	status = tokenize_input(data, data->pipeline);
	if (status != SUCCESS)
		return (status_error(data, status), FAILURE);
	status = syntax(data);
	if (status != SUCCESS)
		return (status_error_syntax(data, status), FAILURE);
	status = merge_tokens_n_rm_blank_tokens(data);
	if (status != SUCCESS)
		return (status_error(data, status), FAILURE);
	status = capture_heredocs(data);
	if (status != SUCCESS)
		return (status_error(data, status), FAILURE);
	debugging(data);
	status = commands_builder(data);
	if (status != SUCCESS)
		return (status_error(data, status), FAILURE);
	debugging(data);
	return (SUCCESS);
}

static t_pars_err	open_file(t_redir *redir)
{
	char *error_msg;
	
	while (redir != NULL)
	{
		if (redir->redir_id == REDIR_IN)
			redir->fd = open(redir->file, O_RDONLY);
		else if (redir->redir_id == REDIR_OUT)
			redir->fd = open(redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (redir->redir_id == REDIR_APPEND)
			redir->fd = open(redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (redir->fd == FAILURE)
		{
			if (redir->redir_id == REDIR_HEREDOC)
				error_msg = ft_strjoin("minishell: ", "heredoc file");
			else
				error_msg = ft_strjoin("minishell: ", redir->file);
			if (error_msg == NULL)
				return (ERROR_MEM_ALLOC);
			perror(error_msg);
			return (FAILURE);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}
void	parsing_and_execution(t_main_data *data)
{
	t_command	*cmd;
	t_pars_err	status;

	if (parser(data) != SUCCESS)
		return ;
	cmd = data->cmds;
	while (cmd != NULL)
	{
		status = open_file(cmd->redir_list);
		if (status != SUCCESS)
		{
			if (status == ERROR_MEM_ALLOC)
				status_error(data, status);
			return ;
		}
		cmd = cmd->next;
	}
	distribution(data); //exec
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_file_descriptors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:12:40 by filipe            #+#    #+#             */
/*   Updated: 2025/04/19 16:24:42 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

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

static void	right_associate_redirects(t_redir *redir, t_command *cmd)
{
	t_redir	*tmp;

	tmp = redir;
	while (redir != NULL)
	{
		if (redir->redir_id == REDIR_APPEND || redir->redir_id == REDIR_OUT)
			cmd->outfile = redir;
		else
			cmd->infile = redir;
		redir = redir->next;
	}
	while (tmp != NULL)
	{
		if (tmp != cmd->infile && tmp != cmd->outfile)
			close(tmp->fd);
		tmp = tmp->next;
	}
}

t_pars_err setup_file_descriptors(t_command *cmd, t_main_data *data)
{
	t_pars_err	status;

	if (cmd != NULL)
	{
		status = open_file(cmd->redir_list);
		if (status != SUCCESS)
		{
			if ((set_exit_env_status(data->env_vars, EXIT_FAIL) == ERROR_MEM_ALLOC)\
				|| status == ERROR_MEM_ALLOC)
				status_error(data, status);
			return (FAILURE);
		}
		right_associate_redirects(cmd->redir_list, cmd);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

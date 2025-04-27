/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:29:45 by filipe            #+#    #+#             */
/*   Updated: 2025/04/27 20:42:41 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "tokenization.h"
#include "execution.h"

t_pars_err	parser(t_main_data *data)
{
	t_pars_err	status;

	status = tokenize_input(data, data->pipeline);
	if (status != SUCCESS)
		return (status_error(data, status), status);
	//debugging(data);
	status = syntax(data);
	if (status != SUCCESS)
		return (status_error_syntax(data, status), status);
	status = merge_tokens_n_rm_blank_tokens(data);
	if (status != SUCCESS)
		return (status_error(data, status), status);
	//debugging(data);
	status = capture_heredocs(data);
	if (status != SUCCESS)
		return (status_error(data, status), status);
	status = commands_builder(data);
	if (status != SUCCESS)
		return (status_error(data, status), status);
	//debugging(data);
	return (SUCCESS);
}

void	parsing_and_execution(t_main_data *data)
{
	t_pars_err	status;

	if (data->pipeline == NULL)
		return ;
	if (*(data->pipeline) == '\0')
		return ;
	status = parser(data);
	if (status != SUCCESS)
	{
		if (status == HEREDOC_CHILD_SIGNALED)
			return ;
		else if (set_exit_env_status(data->env_vars, \
			EXIT_SYNTAX) == ERROR_MEM_ALLOC)
			status_error(data, ERROR_MEM_ALLOC);
		return ;
	}
	create_envp_array(data, data->env_vars);
	// debugging(data);
	execution(data, data->cmds);
}

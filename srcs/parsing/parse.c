/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:29:45 by filipe            #+#    #+#             */
/*   Updated: 2025/04/23 15:37:58 by yulpark          ###   ########.fr       */
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
	return (SUCCESS);
}

void	parsing_and_execution(t_main_data *data)
{
	if (parser(data) != SUCCESS)
	{
		if (set_exit_env_status(data->env_vars, EXIT_SYNTAX) == ERROR_MEM_ALLOC)
			status_error(data, ERROR_MEM_ALLOC);
		return ;
	}
	create_envp_array(data, data->env_vars);
	//debugging(data);
	execution(data, data->cmds);
	// echo(data->cmds->args);
	// distribution(data); //exec
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:17:50 by flima             #+#    #+#             */
/*   Updated: 2025/03/31 19:26:44 by flima            ###   ########.fr       */
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

void	clean_temp_data(t_main_data *data)
{
	free_tokens(data->tokens);
	free(data->pipeline);
	data->pipeline = NULL;
	data->tokens = NULL;
}

void	clean_all_data_exit(t_main_data *data, int out_status)
{
	rl_clear_history();
	//set_terminal
	free_env_vars(data->env_vars);
	free_tokens(data->tokens);
	free(data->pipeline);
	exit(out_status);
}

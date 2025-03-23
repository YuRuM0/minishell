/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:17:50 by flima             #+#    #+#             */
/*   Updated: 2025/03/23 23:07:44 by filipe           ###   ########.fr       */
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

void	clean_all_data(t_main_data *data)
{
	free_tokens(data->tokens);
	data->tokens = NULL;
	free(data->pipeline);
}

void	clean_all_data_error(t_main_data *data, int out_status)
{
	rl_clear_history();
	//set_terminal
	free_tokens(data->tokens);
	free(data->pipeline);
	data->tokens = NULL;
	data->pipeline = NULL;
	exit(out_status);
}

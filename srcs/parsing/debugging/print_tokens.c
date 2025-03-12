/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:04:19 by flima             #+#    #+#             */
/*   Updated: 2025/03/12 17:25:10 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

static void	get_str_type(char **tokens)
{
	tokens[0] = "SPACE_CHAR";
	tokens[1] = "TAB_CHAR";
	tokens[2] = "NEW_LINE";
	tokens[3] = "PIPE";
	tokens[4] = "LESS";
	tokens[5] = "GREAT";
	tokens[6] = "VARIABLE";
	tokens[7] = "D_QUOTE";
	tokens[8] = "S_QUOTE";
	tokens[9] = "WORD";
	tokens[10] = "APPEND";
	tokens[11] = "HEREDOC";
}

static	void	print_token(t_token *token, int i)
{
	char	*str_tok[12];

	get_str_type(str_tok);
	if (i == 0)
	{
		printf("%-10s %-20s %-20s\n", "token", "token_type", "token_value");
		printf("--------------------------------------------\n");
	}
	printf("%-10d %-20s %-20s\n", i, str_tok[token->type], token->value);
}

void	debugging(t_main_data *data)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = data->tokens;
	while (tmp != NULL)
	{
		print_token(tmp, i);
		tmp = tmp->next;
		i++;
	}
}

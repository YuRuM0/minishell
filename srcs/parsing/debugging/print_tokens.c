/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:04:19 by flima             #+#    #+#             */
/*   Updated: 2025/03/11 14:26:23 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**get_str_type(void)
{
	char **tokens;

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
	return (tokens);
}

static	void	print_token(t_token *token, int i)
{
	char **str_tok;

	str_tok = get_str_type();
	printf("\n");
	printf("	");
	printf("token(%d)", i);
	printf("	");
	printf ("token_type: |%s|", str_tok[token->type]);
	printf("	");
	printf ("token_value: |%s|", token->value);
	printf("\n");
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

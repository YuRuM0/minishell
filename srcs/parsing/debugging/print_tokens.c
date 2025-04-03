/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:04:19 by flima             #+#    #+#             */
/*   Updated: 2025/04/03 15:52:12 by filipe           ###   ########.fr       */
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
	tokens[9] = "AND";
	tokens[10] = "WORD";
	tokens[11] = "APPEND";
	tokens[12] = "HEREDOC";
}

static void	get_str_cmd(char **cmd)
{
	cmd[0] = "REDIR_IN";
	cmd[1] = "REDIR_HEREDOC";
	cmd[2] = "REDIR_OUT";
	cmd[3] = "REDIR_APPEND";
}
static	void	print_token(t_token *token, int i)
{
	char	*str_tok[13];

	get_str_type(str_tok);
	if (i == 0)
	{
		printf("%-10s %-20s %-20s\n", "token", "token_type", "token_value");
		printf("--------------------------------------------\n");
	}
	printf("%-10d %-20s %-20s\n", i, str_tok[token->type], token->value);
}

static	void	print_commands(t_command *cmd)
{
	char	*str_cmd[4];
	int		i;

	i = 0;
	get_str_cmd(str_cmd);
	printf("%s: %s\n", "Command", cmd->args[0]);
	while (cmd->args[++i] != NULL)
	{
		printf("%s[%d] %-20s\n", "args", i, cmd->args[i]);
	}
	while (cmd->redir_list != NULL)
	{
		if (cmd->redir_list->redir_id == REDIR_HEREDOC)
			printf("REDIR : %s FILE: %s\n", str_cmd[cmd->redir_list->redir_id], cmd->redir_list->fd);
		else
			printf("REDIR : %s FILE: %s\n", str_cmd[cmd->redir_list->redir_id], cmd->redir_list->file);
		cmd = cmd->next;
	}
}

void	debugging(t_main_data *data)
{
	int		i;
	t_token	*tmp;
	t_command *cmd;

	i = 0;
	tmp = data->tokens;
	while (tmp != NULL)
	{
		print_token(tmp, i);
		tmp = tmp->next;
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);
	cmd = data->cmds;
	i = -1;
	if (cmd != NULL)
	{
		print_commands(cmd);
		cmd = cmd->next;
	}
}

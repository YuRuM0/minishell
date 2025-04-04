/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:04:19 by flima             #+#    #+#             */
/*   Updated: 2025/04/04 11:45:10 by filipe           ###   ########.fr       */
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

static	void	print_commands(t_command *cmd, int nb)
{
	char	*str_cmd[4];
	t_redir	*tmp;
	int		i;

	i = 0;
	tmp = cmd->redir_list;
	get_str_cmd(str_cmd);
	printf("%s[%d] %-20s\n", "Command", nb, cmd->args[0]);
	while (cmd->args[++i] != NULL)
	{
		printf("%s[%d] %-20s\n", "args", i, cmd->args[i]);
	}
	while (tmp != NULL)
	{
		
		if (tmp->redir_id == REDIR_HEREDOC)
			printf("REDIR : %-20s fd: %s\n", str_cmd[tmp->redir_id], tmp->fd);
		else
			printf("REDIR : %-20s file_name: %s\n", str_cmd[tmp->redir_id], tmp->file);
		tmp = tmp->next;
	}
	write(STDOUT_FILENO, "\n", 1);
}

void	debugging(t_main_data *data)
{
	int		i;
	t_token	*tmp;
	t_command *cmd;

	i = 0;
	tmp = data->tokens;
	if (data->cmds == NULL)
	{
		while (tmp != NULL)
		{
			print_token(tmp, i);
			tmp = tmp->next;
			i++;
		}
	}
	printf("--------------------------------------------\n");
	cmd = data->cmds;
	i = 0;
	while (cmd != NULL)
	{
		print_commands(cmd, i);
		cmd = cmd->next;
		i++;
	}
}

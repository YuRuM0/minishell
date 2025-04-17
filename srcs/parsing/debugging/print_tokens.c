/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:04:19 by flima             #+#    #+#             */
/*   Updated: 2025/04/17 21:01:22 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

static	void	print_redir(t_redir *redir, char **id)
{
	t_redir	*tmp;

	write(STDOUT_FILENO, "\n\n", 2);
	tmp = redir;
	while (tmp != NULL)
	{
		if (tmp->redir_id == REDIR_HEREDOC)
			printf("ALL REDIR : %-20s fd: %d\n", id[tmp->redir_id], tmp->fd);
		else
			printf("ALL REDIR : %-20s file_name: %-10sfd : %-20d\n", id[tmp->redir_id], \
				tmp->file, tmp->fd);
		tmp = tmp->next;
	}
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
	int		i;

	i = 0;
	get_str_cmd(str_cmd);
	if (cmd->args[0] != NULL)
		printf("%s[%d] %-20s\n", "Command", nb, cmd->args[0]);
	while (cmd->args[0] && cmd->args[++i] != NULL)
		printf("%s[%d] %-20s\n", "args", i, cmd->args[i]);
	if (cmd->infile)
	{
		if (cmd->infile->redir_id == REDIR_HEREDOC)
			printf("ID : %-20s fd: %d\n", str_cmd[cmd->infile->redir_id], cmd->infile->fd);
		else
		printf("ID : %-20s file_name: %-10sfd : %-20d\n", str_cmd[cmd->infile->redir_id], \
			cmd->infile->file, cmd->infile->fd);
	}
	else
		printf("No infile redirection\n");
	if (cmd->outfile)
		printf("ID: %-28s file_name: %-10sfd : %-20d\n", str_cmd[cmd->outfile->redir_id], \
			cmd->outfile->file, cmd->outfile->fd);
	else
		printf("No outfile redirection\n");
	print_redir(cmd->redir_list, str_cmd);
}

void	debugging(t_main_data *data)
{
	int			i;
	t_token		*tmp;
	t_command	*cmd;

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
		write(STDOUT_FILENO, "\n", 1);
		cmd = cmd->next;
		i++;
	}
}

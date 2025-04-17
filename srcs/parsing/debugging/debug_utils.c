/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:41 by filipe            #+#    #+#             */
/*   Updated: 2025/04/17 20:52:48 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	get_str_type(char **tokens)
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

void	get_str_cmd(char **cmd)
{
	cmd[0] = "REDIR_IN";
	cmd[1] = "REDIR_HEREDOC";
	cmd[2] = "REDIR_OUT";
	cmd[3] = "REDIR_APPEND";
}

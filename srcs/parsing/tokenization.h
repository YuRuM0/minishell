/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:08:13 by filipe            #+#    #+#             */
/*   Updated: 2025/02/21 20:31:52 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATIon_H
# define TOKENIZATION_H

# include "minishell.h"

//split the cmd line into token using these syntax
typedef enum s_syntax
{
	PIPE,		// |
	EQUAL,		// =
	REDIR_IN,	// <
	REDIR_OUT,	// >
	HEREDOC,	// <<
	APPEND,		// >>
	VARIABLE,	// $
	D_QUOTE,	// ""
	// S_QUOTE,	// ''
	WORD,		//CMD, CMD_ARG OR VALUE
}	t_syntax;

typedef struct s_token
{
	char			*cont;
	enum s_syntax	token;
	struct s_token	*next;
}					t_token;

// void    parse(t_main_data *data);
// void    check_heredoc(t_main_data *data);
// char    *ft_strtoken(char *str);
#endif
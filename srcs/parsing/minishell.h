/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:59:25 by flima             #+#    #+#             */
/*   Updated: 2025/02/18 22:13:31 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "../../includes/libft.h"

//part of binary tree to hold the cmd's attributes
typedef struct s_cmd_args
{
	int		nbr_of_args;
	char	**args;
	char	*value;
	bool	pipe;
}	t_cmd_args;

//binary tree to save all the commands and their falgs and values.
typedef struct s_commands
{
	struct	s_commands	*next_cmd;
	struct	s_cmd_args	*flags;
}	t_commands;

//main structure to hold all the data 
typedef struct s_main_data
{
	int					nbr_of_cmds;
	char				*infile;
	char				*outfile;
	char				*errfile; //where and when is it used?
	struct	s_commands	cmds;
}	t_main_data;

//split the cmd line into token using these syntax
typedef enum s_syntax
{
	PIPE,		// |
	EQUAL,		// =
	REDIR_IN,	// <
	REDIR_OUT,	// >
	GREATGREAT,	// >>
	LESSLESS,	// <<
	VARIABLE,	// $
	D_QUOTE,	// ""
	S_QUOTE,	// ''
	WORD,		//CMD, CMD_ARG OR VALUE
}	t_syntax;

typedef struct s_token
{
	char			*cont;
	enum s_syntax	token;
	struct s_token	*next;
}					t_token;

#endif
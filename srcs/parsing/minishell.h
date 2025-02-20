/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:59:25 by flima             #+#    #+#             */
/*   Updated: 2025/02/20 21:39:38 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include "../../includes/libft.h"
# include "tokenization.h"

// 
# define METACHAR "<>| "
# define VAR_BLOCK " <>|?\'\"/$"
# define BLANK "\t\n\v\f\r "
# define S_QUOTE '\''
# define D_QUOTES '\"'

typedef struct s_simple_cmd
{
	int		nbr_of_args;
	char	**args;
	char	*value;
	bool	pipe;
}	t_simple_cmd;

//main structure to hold all the data 
typedef struct s_main_data
{	
	int						nbr_of_cmds;
	char					*pipeline;
	char					*heredoc_content;
	char					*infile;
	char					*outfile;
	char					*errfile; //where and when is it used?
	struct	s_simple_cmd	**cmds;
}	t_main_data;

#endif
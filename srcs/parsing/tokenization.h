/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:08:13 by filipe            #+#    #+#             */
/*   Updated: 2025/02/23 17:17:52 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

# define META_CHARS_SET " \t\n|<>\'\"$"

//split the cmd line into token using these syntax
typedef enum e_syntax
{
	SPACE_CHAR,
	TAB_CHAR,          
	NEW_LINE,       // \n (Newline, indicating end of command or separator)
	PIPE,			// | (Pipe)
	EQUAL,         // = (Equal sign)
	REDIR_IN,      // < (Input redirection)
	REDIR_OUT,     // > (Output redirection)
	HEREDOC,       // << (Here-document)
	APPEND,        // >> (Append to output)
	VARIABLE,      // $ (Variable expansion)
	D_QUOTE,       // "" (Double quotes for string)
	S_QUOTE,       // '' (Single quotes for literal string)
	WORD,          // CMD, CMD_ARG or generic string value
} t_syntax;

typedef enum e_parsing_codes //modificar error codes
{
	PARSE_SUCCESS,
	ERR_CMD_SUBSTIT,
	ERR_SYNTAX_NL,
	ERR_UNCLOSED_QUOTES,
	ERR_SYNTAX_OPEN_PAR,
	ERR_SYNTAX_CLOSE_PAR,
	ERR_SYNTAX_PIPE,
	ERR_SYNTAX_OR,
	ERR_SYNTAX_AND,
	ERR_SYNTAX_REDIR,
	ERR_SYNTAX_AMPER,
	ERR_SYNTAX_ERROR,
	ERR_BG_PROCESS,
	ERR_PARSING_ERROR,
	ERR_MEM_ALLOC,
	ERR_EXPAND,
	ERR_CMD,
	SIGINT_HDOC,
}	t_ercode_pars;

typedef enum e_redir_type
{
	REDIR,
	IN,
	HERE,
	OUT,
	APP
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	redir_type;
	int				fd;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redir;
	int					last_in;
	int					last_out;
	struct	s_command	*next;
}						s_command;

typedef struct s_token
{
	char			*value;
	enum e_syntax	type;
	struct s_token	*next;
}					t_token;

t_ercode_pars	tokenize_input(t_main_data *data, char	*input);
t_token			*add_new_token(void);
void			add_token_back(t_token **head, t_token *new);
t_token			*last_token(t_token *list);
#endif
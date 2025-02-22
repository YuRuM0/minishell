/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:08:13 by filipe            #+#    #+#             */
/*   Updated: 2025/02/22 22:22:30 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

//split the cmd line into token using these syntax
typedef enum s_syntax
{
	PIPE,          // | (Pipe)
	EQUAL,         // = (Equal sign)
	REDIR_IN,      // < (Input redirection)
	REDIR_OUT,     // > (Output redirection)
	HEREDOC,       // << (Here-document)
	APPEND,        // >> (Append to output)
	VARIABLE,      // $ (Variable expansion)
	D_QUOTE,       // "" (Double quotes for string)
	S_QUOTE,       // '' (Single quotes for literal string)
	WORD,          // CMD, CMD_ARG or generic string value
	NEW_LINE,       // \n (Newline, indicating end of command or separator)
	//END_OF_INPUT,  // End of input, e.g., EOF
	ERROR,         // Error in tokenization (when a token is unrecognized)
} t_syntax;

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
	int				size;
	enum s_syntax	type;
	struct s_token	*next;
}					t_token;

// void	tokenize_input(t_main_data *data);
// t_token	*add_new_token(void *content, t_syntax type);
// void	creat_token(t_token **head, t_token *new);
#endif
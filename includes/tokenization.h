/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:08:13 by filipe            #+#    #+#             */
/*   Updated: 2025/03/11 18:28:14 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

# define METACHARS " \t\n|<>$\"\'"


//split the cmd line into token using these syntax
typedef enum e_syntax
{
	SPACE_CHAR,
	TAB_CHAR,         // \t (tab) 
	NEW_LINE,       // \n (Newline, indicating end of command or separator)
	PIPE,			// | (Pipe)
	LESS,     // > (Output redirection)
	GREAT,      // < (Input redirection)
	VARIABLE,      // $ (Variable expansion)
	D_QUOTE,       // "" (Double quotes for string)
	S_QUOTE,       // '' (Single quotes for literal string)
	WORD,          // CMD, CMD_ARG or generic string value
	APPEND,       // >> (Append to output)
	HEREDOC,       // << (Here-document)
} t_syntax;

typedef enum e_parsing_err //modificar error codes
{
	SUCCESS,
	ERROR_MEM_ALLOC,
	ERROR_PIPE_START,
	ERROR_CMD_SUBSTITUTION,
	UNCLOSED_QUOTE
}	t_pars_err;

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

//Jump table tokenization 

//Tokanization
t_pars_err			tokenize_input(t_main_data *data, char	*input);
t_token				*add_new_token(void);
void				add_token_back(t_token **head, t_token *new);
t_token				*last_token(t_token *list);
t_syntax			get_token_type(char cha);
//lexer functions
typedef t_pars_err (*t_lex_functions)(char *str, size_t *i, t_syntax *type);
t_pars_err			process_single_quotes(char *input, size_t *i, t_syntax *tok_type);
t_pars_err			process_double_quotes(char *input, size_t *i, t_syntax *tok_type);
t_pars_err			process_word_n_spaces(char *input, size_t *i, t_syntax *tok_type);
t_pars_err			process_pipe(char *input, size_t *i, t_syntax *tok_type);
t_pars_err			process_great_n_herdoc(char *input, size_t *i, t_syntax *tok_type);
t_pars_err			process_less_n_append(char *input, size_t *i, t_syntax *tok_type);
t_pars_err			process_env_var(char *input, size_t *i, t_syntax *tok_type);
//debugging
void				debugging(t_main_data *data);
//free functions
void	free_tokens(t_token **tokens);
#endif

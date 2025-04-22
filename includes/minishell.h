/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:59:25 by flima             #+#    #+#             */
/*   Updated: 2025/04/22 16:01:37 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include <signal.h>

//# include "../execution/execution.h"

# define _GNU_SOURCE


//mix of brasilian and corean flags haha
# define MINISHELL_PROMPT \
"\001\033[38;5;46m\002m\001\033[38;5;154m\002i\001\033[38;5;226m\002n\
\001\033[38;5;190m\002i\001\033[38;5;33m\002s\001\033[38;5;21m\002h\
\001\033[38;5;160m\002e\001\033[38;5;196m\002l\001\033[38;5;255m\002l\
\001\033[38;5;240m\002$\001\033[0m\002 "

extern int	g_last_signal;

typedef enum e_exit_code
{
	EXIT_SUCCESSFULLY = 0,
	EXIT_FAIL = 1,
	EXIT_SYNTAX,
	EXIT_MEM_FAILURE = 3, //should be 137?
	EXIT_DENIED,
	EXIT_CHILD_FAILURE,
	EXIT_CMD_NOT_EXECUTABLE = 126,
	EXIT_CMD_NOT_FOUND = 127,
	EXIT_SIGNAL_CODE = 128,
	EXIT_SIGINT = 130,
	EXIT_SIGQUIT = 131
}	t_exit_code;

# define PARENT 1
# define CHILD 2

//main structure to hold all the data
typedef struct s_main_data
{
	int						nbr_of_cmds;
	char					*pipeline;
	int						last_fd_in;
	int						exit_status;
	struct s_env_var		*env_vars;
	struct s_command		*cmds;
	struct s_token			*tokens;
	char					**envp_array;
}							t_main_data;

typedef enum	e_signal_mode
{
	INTERACTIVE,
	NON_INTERACTIVE,
	HEREDOC_CHILD,
	CMD_CHILD,
	CMD_PARENT,
}				t_signal_mode;

void		parsing_and_execution(t_main_data *data);
void		error_msg(char *msg);
void		handle_signal_main_loop();
void		setup_signal_handlers(t_signal_mode	mode);


#endif

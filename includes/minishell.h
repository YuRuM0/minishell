/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:59:25 by flima             #+#    #+#             */
/*   Updated: 2025/04/10 22:04:00 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
#include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include <signal.h>
//# include "../execution/execution.h"

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
	EXIT_DENIED,
	EXIT_MEM_FAILURE = 3, //should be 137?
	EXIT_CHILD_FAILURE,
	EXIT_CMD_NOT_EXECUTABLE = 126,
	EXIT_CMD_NOT_FOUND = 127,
	EXIT_SIGNAL_CODE = 128,
	EXIT_SIGINT = 130,
	EXIT_SIGQUIT = 131
}	t_exit_code;
//main structure to hold all the data
typedef struct s_main_data
{
	int						nbr_of_cmds;
	char					*pipeline;
	int						exit_status;
	struct s_env_var		*env_vars;
	struct s_command		*cmds;
	struct s_token			*tokens;
}							t_main_data;


void	parser(t_main_data *data);
void	error_msg(char *msg);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:24:38 by flima             #+#    #+#             */
/*   Updated: 2025/03/12 17:14:40 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

static char	*read_tty(void)
{
	char	*pipeline;

	pipeline = readline(MINISHELL_PROMPT);
	if (pipeline == NULL && errno == ENOMEM)
	{
		perror("minishell");
		exit(EXIT_MEM_FAILURE);
	}
	else if (pipeline == NULL && errno == 0)
	{
		rl_clear_history();
		//set teminal tcgetattr function, learn it
		error_msg("exit\n");
		exit(EXIT_SUCCESSFULLY);
	}
	if (pipeline && ft_strlen(pipeline))
		add_history(pipeline);
	return (pipeline);
}

static void	loop_minishell(t_main_data *data)
{
	while (true)
	{
		data->pipeline = read_tty();
		// data->tty_line += 1;
		parser(data);
		clean_all_data(data);
	}
}

static void	init_data(t_main_data *data)
{
	data->nbr_of_cmds = 0;
	data->tty_line = 0;
	data->heredoc_content = NULL;
	data->cmds = NULL;
	data->tokens = NULL;
	data->errfile = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_main_data	data;

	(void)argv;
	(void)envp;
	if (argc != 1)
	{
		ft_putstr_fd("Error\n No arguments needed", 2);
		return (1);
	}
	//signals func
	init_data(&data);
	loop_minishell(&data);
	return (0);
}

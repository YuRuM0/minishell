/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:24:38 by flima             #+#    #+#             */
/*   Updated: 2025/04/27 17:09:13 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int			g_last_signal;

static char	*read_tty(void)
{
	char	*pipeline;

	pipeline = readline(MINISHELL_PROMPT);
	if (pipeline == NULL && errno == ENOMEM)
	{
		error_msg(NULL);
		exit(EXIT_MEM_FAILURE);
	}
	else if (pipeline == NULL && errno == 0)
	{
		rl_clear_history();
		error_msg("exit\n");
		exit(EXIT_SUCCESSFULLY);
	}
	if (pipeline && ft_strlen(pipeline))
		add_history(pipeline);
	return (pipeline);
}

static char	*read_file(void)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (line == NULL && errno == ENOMEM)
	{
		error_msg(NULL);
		exit(EXIT_MEM_FAILURE);
	}
	else if (line == NULL && errno == 0)
		exit(EXIT_SUCCESSFULLY);
	return (line);
}

static void	loop_minishell(t_main_data *data)
{
	while (true)
	{
		handle_signal_main_loop();
		if (isatty(STDIN_FILENO))
			data->pipeline = read_tty();
		else
			data->pipeline = read_file();
		if (data->pipeline == NULL)
			break ;
		setup_signal_handlers(NON_INTERACTIVE);
		parsing_and_execution(data);
		clean_temp_data(data);
	}
}

void	init_data(t_main_data *data)
{
	data->nbr_of_cmds = 0;
	data->last_fd_in = STDIN_FILENO;
	data->pipeline = NULL;
	data->envp_array = NULL;
	data->cmds = NULL;
	data->tokens = NULL;
	data->exit_status = 0;
	data->env_vars = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_main_data	data;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error\n No arguments needed", 2);
		return (1);
	}
	init_data(&data);
	duplicate_env_var(&data, envp);
	loop_minishell(&data);
	clean_all_data_exit(&data, 0);
	return (0);
}

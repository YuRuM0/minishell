/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:24:38 by flima             #+#    #+#             */
/*   Updated: 2025/02/21 20:32:31 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_tty(void)
{
	char	*pipeline;

	pipeline = readline("\033[1;35mminishell$ \033[0m");
	if (pipeline == NULL && errno == ENOMEM)
	{
		write(STDOUT_FILENO, "error reading input", 20); // temp
		//error_msg - exit minishel, memory alocation fails
	}
	else if (pipeline == NULL && errno == 0) // dignal ctrl + D
	{
		write(STDOUT_FILENO, "exit\n", 6);
		rl_clear_history();
		//set teminal tcgetattr function, learn it
		exit(1);
	}
	if (pipeline && ft_strlen(pipeline))
		add_history(pipeline); //add here?
	return (pipeline);
}

static void	loop_minishell(t_main_data *data)
{	
	while (true)
	{
		data->pipeline = read_tty();
		parse(data);
		
	}	
	
}
int	main(int argc, char **argv, char **envp)
{
	t_main_data	data;

	(void)argv;
	// if (argc != 1)
	// {
	// 	ft_putstr_fd("Error\n No arguments needed", 2);
	// 	return (1);
	// }
	//signals func
	loop_minishell(&data);
	return (0);
}

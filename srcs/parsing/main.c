/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:24:38 by flima             #+#    #+#             */
/*   Updated: 2025/02/18 22:16:26 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_minishell(t_main_data data)
{
	char	*pipeline;

	while (1)
	{
		pipeline = readline("minishell42>");
		
	}
	
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
	//signals func
	
	return (0);
}
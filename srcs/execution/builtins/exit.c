/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:22:40 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/18 18:35:37 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
// check extra leaks

static int	ft_isnum(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_one_arg(char **cmd, t_main_data *data)
{
	int	exit_code;

	if (ft_isnum(cmd[1]) != 1)
	{
		write(1, "exit: non-numeric argument\n", 28);
		clean_all_data_exit(data, 2);
	}
	exit_code = ft_atoi(cmd[1]);
	write(1, "exit\n", 5);
	clean_all_data_exit(data, exit_code %= 256);
	//exit status: 0-255 exit(256) = exit(0)
}

static void	exit_multi_arg(char **cmd, t_main_data *data)
{
	if (ft_isnum(cmd[1]) != 1)
	{
		write(1, "exit: non-numeric argument\n", 28);
		clean_all_data_exit(data, 2);
	}
	else
	{
		write(1, "exit\n", 5);
		write(1, "exit: too many arguments\n", 26);
		exit(2);
	}
}

void	ft_exit(char **cmd, t_main_data *data)
{
	if (!cmd[1])
	{
		write(1, "exit\n", 5);
		clean_all_data_exit(data, 0);
	}
	if (cmd[1] && !cmd[2])
		exit_one_arg(cmd, data);
	else if (cmd[1] && cmd[2])
		exit_multi_arg(cmd, data);
}

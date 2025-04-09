/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dots.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:36:26 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/09 17:18:56 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "execution.h"

// counting the number of .. :dots_counter
// truncate PWD              : truncate
// save the new folders
// ft_strputjoin
// change env using export

int	dots_counter(char *cmd)
{
	int	i;
	int dots;

	i = 0;
	dots = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '.' && cmd[i + 1])
		{
			i++;
			if (cmd[i] == '.' && (cmd[i + 1] && (cmd[i + 1] == '/')|| !cmd[i + 1]))
				dots += 1;
		}
		i++;
	}
	return (dots);
}

char	*truncate(int dots, char *variable)
{
	size_t	i;
	char *trunc_pwd;

	i = strlen(variable) + 1;
	while (i >= 0 && dots > 0)
	{
		if (variable[i] == '/')
			dots--;
		i--;
	}
	trunc_pwd = ft_substr(variable, 0, i + 1);
	if (!trunc_pwd)
		return (MALLOC_FAIL);
	return (trunc_pwd);
}
*/

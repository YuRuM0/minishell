/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dots.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:36:26 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/11 17:50:54 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// counting the number of .. :dots_counter
// truncate PWD              : truncate
// save the new folders		 : folder_saver
// ft_strputjoin			 : already have
// change env using export

static int	dots_counter(char *cmd)
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
			if (cmd[i] == '.' && cmd[i + 1] && ((cmd[i + 1] == '/') || !cmd[i + 1]))
				dots += 1;
		}
		i++;
	}
	return (dots);
}

static char	*truncater(int dots, char *variable)
{
	size_t	i;
	char *trunc_pwd;

	i = ft_strlen(variable) + 1;
	while (i > 0 && dots > 0)
	{
		if (variable[i] == '/')
			dots--;
		i--;
	}
	trunc_pwd = ft_substr(variable, 0, i + 1);
	if (!trunc_pwd)
		return (NULL);
	return (trunc_pwd);
}

static char	*folder_saver(char *cmd)
{
	int i;
	char	*res;

	i = ft_strlen(cmd) + 1;
	if (cmd[i] == '.' && cmd[i - 1] == '.' && cmd[i - 2] == '/')
		return (NULL);
	while (cmd[i] != '/')
		i--;
	res = ft_substr(cmd, i, ft_strlen(cmd) - i + 1);
	return (res);
}

t_exec_error ft_cd_dots(char *cmd, t_env_var *envp, t_env_var *PWD)
{
	 int	dots;
	 char	*folder;
	 char	*truncated;
	 char 	*new_path;

	 dots = dots_counter(cmd);
	 folder = folder_saver(cmd);
	 if (!folder)
	 	return (MALLOC_FAIL);
	 truncated = truncater(dots, envp->variable);
	 if (truncated == NULL)
	 	return (MALLOC_FAIL);
	 new_path = ft_strputjoin(truncated, folder, '/');
	 if (new_path == NULL)
	 	return (MALLOC_FAIL);
	 absolute_path(new_path, &envp, PWD);
	 return (SUCCEED);
}
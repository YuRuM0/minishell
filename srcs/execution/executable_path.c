/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:43:32 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/24 16:23:30 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_strputjoin(char *src1, char *src2, char c)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	dst = malloc(ft_strlen(src1) + ft_strlen(src2) + 2);
	if (!dst || !src1 || !src2)
		return (NULL);
	while (src1 && src1[i])
		dst[j++] = src1[i++];
	dst[j] = c;
	j++;
	i = 0;
	while (src2 && src2[i])
		dst[j++] = src2[i++];
	dst[j] = '\0';
	return (dst);
}

void	free_double(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	is_exec_file(t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "/", 1) != 0)
		return (1);
	return (0);
}

char	*executable_path(t_main_data *data, t_command *cmd)
{
	char		**env_path_var;
	t_env_var	*env_path;
	int			i;
	char		*path;

	if (is_exec_file(cmd) == 0)
		return (cmd->args[0]);
	env_path = ft_find_env(data->env_vars, "PATH");
	env_path_var = ft_split(env_path->variable, ':');
	if (!env_path_var)
		return (NULL);
	i = 0;
	while (env_path_var[i])
	{
		path = ft_strputjoin(env_path_var[i], cmd->args[0], '/'); // leak
		if (access(path, X_OK | F_OK) == 0)
		{
			free_double(env_path_var);
			return (path);
		}
		free(path);
		i++;
	}
	free_double(env_path_var);
	return (NULL);
}

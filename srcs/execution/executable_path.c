/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:43:32 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/27 17:36:31 by flima            ###   ########.fr       */
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

static char *check_executable_file(t_main_data *data, t_command *cmd, char *file)
{
	struct stat	buf;

	if (cmd->args[0][0] == '\0')
		return (NULL);
	if (stat(file, &buf) != 0)
	{
		data->exit_status = EXIT_CMD_NOT_FOUND;
		return (NULL);
	}
	if (access(file, F_OK) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			errno = EISDIR;
		else if (access(file, R_OK | X_OK) == 0)
			return (file);
		data->exit_status = EXIT_CMD_NOT_EXECUTABLE;
		return (NULL);
	}
	data->exit_status = EXIT_CMD_NOT_FOUND;
	return (NULL);
}

static bool	is_exec_file(t_command *cmd)
{
	if (cmd->args[0][0] == '\0')
		return (true);
	if (!ft_strncmp(cmd->args[0], "./", 2) || cmd->args[0][0] == '/')
		return (true);
	return (false);
}

char	*executable_path(t_main_data *data, t_command *cmd, char **env_path_var, int i)
{
	t_env_var	*env_path;
	char		*path;

	if (is_exec_file(cmd) == true)
		return (check_executable_file(data, cmd, cmd->args[0]));
	env_path = ft_find_env(data->env_vars, "PATH");
	if (!env_path)
		return (NULL);
	env_path_var = ft_split(env_path->variable, ':');
	if (!env_path_var)
		return (NULL);
	while (env_path_var[i])
	{
		path = ft_strputjoin(env_path_var[i], cmd->args[0], '/');
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:41:37 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/23 21:55:00 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	cases(char *cmd, t_env_var **envp, char *tb_old_pwd)
{
	char		*new_pwd;
	struct stat	stats;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &stats) != 0)
			return (3);
		if (chdir(cmd) != 0)
			return (1);
		new_pwd = getcwd(NULL, 0);
		change_pwd(envp, tb_old_pwd, new_pwd);
		return (0);
	}
	return (2);
}

static t_exec_error	ft_cd(char **cmd, t_main_data *data, char *path)
{
	int		res;

	if (cmd[1] == NULL)
	{
		if (go_home(&data->env_vars, path) == 1)
			error_msg("cd: HOME doesn't exist\n");
	}
	else if (cmd[1][0] == '-')
	{
		if (go_prev(&data->env_vars, path) == 1)
			error_msg("cd: OLDPWD doesn't exist\n");
	}
	else
	{
		res = cases(cmd[1], &data->env_vars, path);
		if (res == 1)
			error_msg("cd: no such file or directory\n");
		else if (res == 3)
			error_msg("cd: not a directory\n");
		else if (res == 2)
			error_msg("cd: permission denied\n");
	}
	return (SUCCEED);
}

t_exec_error	cd(char **cmd, t_main_data *data)
{
	char	*formatted_path;
	char	*tb_old_pwd;

	if (cmd[1] && cmd[2])
		error_msg("cd: Too many arguments\n");
	tb_old_pwd = getcwd(NULL, 0);
	formatted_path = ft_strjoin("OLDPWD=", tb_old_pwd);
	return (ft_cd(cmd, data, formatted_path));
}

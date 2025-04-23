/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:41:37 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/23 15:48:20 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	change_pwd(t_env_var **envp, char *tb_oldpwd, char *pwd)
{
	t_env_var	*temp;

	temp = *envp;
	while (temp)
	{
		if (ft_strncmp(temp->variable, "OLDPWD", 6) == 0)
		{
			free(temp->variable);
			temp->variable = ft_strdup(tb_oldpwd);
		}
		if (ft_strncmp(temp->variable, "PWD", 3) == 0)
		{
			free (temp->variable);
			temp->variable = ft_strdup(pwd);
		}
		temp = temp->next;
	}
}

static int	go_home(t_env_var **envp, char *oldpwd)
{
	t_env_var	*home;
	char		*new_path;

	home = ft_find_env(*envp, "HOME");
	new_path = ft_strchr(home->variable, '=');
	new_path++;
	if (!new_path || chdir(new_path) != 0)
		return (1);
	change_pwd(envp, oldpwd, home->variable);
	return (0);
}

static int	go_prev(t_env_var **envp, char *tb_old_pwd)
{
	t_env_var	*tb_new_pwd;
	char		*new_path;

	tb_new_pwd = ft_find_env(*envp, "OLDPWD");
	new_path = ft_strchr(tb_new_pwd->variable, '=');
	new_path++;
	if (!new_path || chdir(new_path) != 0)
		return (1);
	free(new_path);
	change_pwd(envp, tb_old_pwd, tb_new_pwd->variable);
	return (0);
}

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

t_exec_error	ft_cd(char **cmd, t_main_data *data)
{
	char	*tb_old_pwd;
	char	*formatted_path;
	int		res;

	if (cmd[1] && cmd[2])
		error_msg("cd: Too many arguments\n");
	tb_old_pwd = getcwd(NULL, 0);
	formatted_path = ft_strjoin("OLDPWD=", tb_old_pwd);
	if (cmd[1] == NULL || cmd[1][0] == '~')
	{
		if (go_home(&data->env_vars, formatted_path) == 1)
			error_msg("cd: HOME doesn't exist\n");
	}
	else if (cmd[1][0] == '-')
	{
		if (go_prev(&data->env_vars, formatted_path) == 1)
			error_msg("cd: OLDPWD doesn't exist\n");
	}
	else
	{
		res = cases(cmd[1], &data->env_vars, formatted_path);
		if (res == 1)
			error_msg("cd: no such file or directory\n");
		else if (res == 3)
			error_msg("cd: not a directory\n");
		else if (res == 2)
			error_msg("cd: permission denied\n");
	}
	return (SUCCEED);
}

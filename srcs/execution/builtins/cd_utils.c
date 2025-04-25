/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:20:38 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/25 18:20:50 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	change_pwd(t_env_var **envp, char *tb_oldpwd, char *pwd)
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

int	go_home(t_env_var **envp, char *oldpwd, t_main_data *data)
{
	t_env_var	*home;
	char		*new_path;

	home = ft_find_env(*envp, "HOME");
	new_path = ft_strchr(home->variable, '=');
	if (!new_path)
		status_error(data, ERROR_MEM_ALLOC);
	new_path++;
	if (!new_path || chdir(new_path) != 0)
		return (1);
	change_pwd(envp, oldpwd, home->variable);
	return (0);
}

int	go_prev(t_env_var **envp, char *tb_old_pwd)
{
	t_env_var	*tb_new_pwd;
	char		*new_path;

	tb_new_pwd = ft_find_env(*envp, "OLDPWD");
	new_path = ft_strchr(tb_new_pwd->variable, '=');
	new_path++;
	if (!new_path || chdir(new_path) != 0)
		return (1);
	change_pwd(envp, tb_old_pwd, tb_new_pwd->variable);
	return (0);
}

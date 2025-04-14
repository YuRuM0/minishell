/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cases.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:46:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/14 16:41:57 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
// t_exec_error set_env(t_env_var **envp, char *var)

t_exec_error	go_home(t_env_var **envp, t_env_var *PWD)
{
	char	*path;
	char	*cwd;
	char	*oldpwd;
	char	*pwd;

	path = getenv("HOME");
	if (!path)
		return (FAIL_PATH_RETRIEVAL);
	if (chdir(path) != 0)
	{
		error_msg("minishell: cd: Failed to change the path");
		return (FAIL_PATH_RETRIEVAL);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (FAIL_PATH_RETRIEVAL);
	oldpwd = update_env_value("OLDPWD=", PWD->variable);
	pwd = update_env_value("PWD=", cwd);
	free(cwd);
	if (!oldpwd || !pwd)
		return (MALLOC_FAIL);
	if (set_env(envp, oldpwd) != SUCCEED || set_env(envp, pwd) != SUCCEED)
	{
		error_msg("minishell: cd: Failed to update the env");
		return (ENV_ERROR);
	}
	return (SUCCEED);
}

t_exec_error	go_prev(t_env_var **envp,  t_env_var *PWD, t_env_var *OLDPWD)
{
	char	*path_curr;
	char	*path_old;

	path_old = update_env_value("OLDPWD=", PWD->variable);
	path_curr = update_env_value("PWD=", OLDPWD->variable);
	if (!path_old || !path_curr)
		return (MALLOC_FAIL);
	if (set_env(envp, path_old) != SUCCEED || set_env(envp, path_curr) != SUCCEED)
	{
		error_msg("minishell: cd: Failed to update the env");
		return (ENV_ERROR);
	}
	free(path_old);
	free(path_curr);
	return (SUCCEED);
}

t_exec_error	relative_path(char *cmd, t_env_var **envp, t_env_var *PWD)
{
	char	*new_path;
	char	*path_curr;
	char	*path_old;

	new_path = ft_strputjoin(PWD->variable, cmd, '/');
	if (!chdir(new_path))
	{
		error_msg("minishell: cd: No such file or directory");
		return (INVALID_INPUT);
	}
	path_old = update_env_value("OLDPWD=", PWD->variable);
	path_curr = update_env_value("PWD=", new_path);
	if (!path_old || !path_curr)
		return (MALLOC_FAIL);
	if (set_env(envp, path_old) != SUCCEED || set_env(envp, path_curr) != SUCCEED)
	{
		error_msg("minishell: cd: Failed to update the env");
		return (ENV_ERROR);
	}
	free(path_old);
	free(path_curr);
	return (SUCCEED);
}

t_exec_error	absolute_path(char *cmd, t_env_var **envp, t_env_var *PWD)
{
	char	*path_curr;
	char	*path_old;
	char	*cwd;

	if (!chdir(cmd))
	{
		error_msg("minishell: cd: No such file or directory");
		return (INVALID_INPUT);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (FAIL_PATH_RETRIEVAL);
	path_old = update_env_value("OLDPWD=", PWD->variable);
	path_curr = update_env_value("PWD=", cwd);
	if (!path_curr || !path_old)
		return (MALLOC_FAIL);
	if (set_env(envp, path_old) != SUCCEED || set_env(envp, path_curr) != SUCCEED)
	{
		error_msg("minishell: cd: Failed to update the env");
		return (ENV_ERROR);
	}
	free(path_old);
	free(path_curr);
	return (SUCCEED);
}

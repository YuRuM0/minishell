/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:46:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/08 17:15:04 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//t_exec_error	go_home(char *PWD, char *OLDPWD)
//{
//	char	*path;

//	path = getenv("HOME");
//	if(!path)
//		return (FAIL_PATH_RETRIEVAL);
//	chdir(path);
//	free(OLDPWD);
//	OLDPWD = update_env_value(OLDPWD, PWD);
//	free(PWD);
//	PWD = update_env_value(PWD, path);
//	if (!OLDPWD || !PWD)
//		return (MALLOC_FAIL);
//	return (SUCCEED);
//}

// t_exec_error	go_prev(char *PWD, char *OLDPWD)
// {
// 	char	*temp;
// 	char	*old;

// 	temp = ft_strdup(PWD);
// 	old = ft_strdup(OLDPWD);
// 	if (!temp || !old)
// 		return (MALLOC_FAIL);
// 	free(PWD);
// 	PWD = update_env_value(temp, OLDPWD);
// 	if (!PWD)
// 	{
// 		free(temp);
// 		free(old);
// 		return (MALLOC_FAIL);
// 	}
// 	free(OLDPWD);
// 	OLDPWD = update_env_value(old, temp);
// 	if (!OLDPWD)
// 	{
// 		free(temp);
// 		free(old);
// 		return (MALLOC_FAIL);
// 	}
// 	free(temp);
// 	free(old);
// 	return (SUCCEED);
// }

//t_exec_error	relative_path(char *cmd, t_env_var **envp)
//{
//	char	*new_path;
//	char	*PWD;
//	char	*OLDPWD;
//	char	*temp;

//	PWD = ft_find_env(&envp, "PWD");
//	OLDPWD = ft_findenv(&envp, "OLDPWD");
//	new_path = ft_strputjoin(PWD, cmd, '/');
//	if (!chdir(new_path))
//	{
//		error_msg("minishell: cd: No such file or directory");
//		return (INVALID_INPUT);
//	}
//	free(OLDPWD);
//	OLDPWD = update_env_value("OLDPWD=", PWD);
//	if (!OLDPWD)
//		return (MALLOC_FAIL);
//	free(PWD);
//	PWD = update_env_value("PWD=", new_path);
//	if (!PWD)
//		return (MALLOC_FAIL);
//	return (SUCCEED);
//}

//t_exec_error	absolute_path(char *cmd, t_env_var **envp)
//{
//	char	*PWD;
//	char	*OLDPWD;

//	PWD = ft_find_env(&envp, "PWD");
//	OLDPWD = ft_findenv(&envp, "OLDPWD");
//	if (!chdir(cmd))
//	{
//		error_msg("minishell: cd: No such file or directory");
//		return (INVALID_INPUT);
//	}
//	free(OLDPWD);
//	OLDPWD = update_env_value("OLDPWD=", PWD);
//	if (!OLDPWD)
//		return (MALLOC_FAIL);
//	free(PWD);
//	PWD = update_env_value("PWD=", cmd);
//	if (!PWD)
//		return (MALLOC_FAIL);
//	return (SUCCEED);
//}
//t_exec_error	ft_cd(char **cmd, t_env_var **envp)
//{
//	char	*PWD;
//	char	*OLDPWD;

//	if (input_counter(cmd) != SUCCEED)
//		return (INVALID_INPUT);
//	PWD = ft_find_env(&envp, "PWD");
//	OLDPWD = ft_findenv(&envp, "OLDPWD");
//	if (!cmd)
//		return (NO_INPUT);
//	if (!cmd[1] || (cmd[1][0] == '~' && !cmd[2]))
//		go_home(PWD, OLDPWD);
//	else if (cmd[1][0] == '-' && !cmd[2])
//		go_prev(PWD, OLDPWD);
//	else if (cmd[1][0] != '/')
//		relative_path(cmd[1], envp);
//	else if (cmd[1][0] == '/')
//		absolute_path(cmd[1], envp);
//	//handle .. cases: cd .. or cd ../../
//	return (SUCCEED);
//}

////// must be a checker that checks the number of input
////int ft_cd(char *path, t_address add_list)
////{
////	char *current_dir;
////	char *temp;
////	char *joined;

////	current_dir = getcwd(NULL, 0);
////	if (!current_dir)
////		return (perror("getcwd fail"), -1);
////	if (path[0] != '/')
////	{
////		joined = ft_strputjoin(current_dir, path, '/');
////		if (!joined)
////		{
////			free(joined);
////			return (-1);
////		}
////		path = joined;
////	}
////	if (chdir(path) != 0)
////		return (perror("No such file or directory."), -1);
////	if (add_list.prev)
////        add_list.prev->address = current_dir;
////    add_list.address = ft_strdup(path);
////	return (0);
////}

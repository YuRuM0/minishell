/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:46:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/08 14:44:51 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//static char	*ft_strputjoin(char *src1, char *src2, char c)
//{
//	int	i;
//	int	j;
//	char *dst;

//	i = 0;
//	j = 0;
//	dst = malloc(ft_strlen(src1) + ft_strlen(src2) + 2);
//    if (!dst)
//         return NULL;
//	if (!src1 || !src2)
//		return (0);
//	while (src1 && src1[i])
//	{
//		dst[j] = src1[i];
//		i++;
//		j++;
//	}
//	dst[j] = c;
//	j++;
//	i = 0;
//	while (src2 && src2[i])
//	{
//		dst[j] = src2[i];
//		j++;
//		i++;
//	}
//	dst[j] = '\0';
//	return (dst);
//}

t_exec_error go_home(char *PWD, char *OLDPWD)
{
	char *path;

	path = getenv("HOME");
	if(!path)
		return (FAIL_PATH_RETRIEVAL);
	chdir(path);
	free(OLDPWD);
	OLDPWD = ft_strdup(PWD);
	free(PWD);
	PWD = ft_strdup(path);
	return (SUCCEED);
}

t_exec_error go_prev(char *PWD, char *OLDPWD)
{
	char *temp;

	if (OLDPWD)
	{
		error_msg("minishell: cd : OLDPWD not set");
		return (ENV_ERROR);
	}
	temp = ft_strdup(PWD);
	if (!temp)
		return (MALLOC_FAIL);
	free(PWD);
	PWD = ft_strdup(OLDPWD);
	if (!PWD)
		return (MALLOC_FAIL);
	free(OLDPWD);
	OLDPWD = ft_strdup(temp);
	if (!OLDPWD)
		return (MALLOC_FAIL);
	free(temp);
	return (SUCCEED);
}

t_exec_error ft_cd(char **cmd, t_env_var *envp)
{
	char *PWD;
	char *OLDPWD;

	if (find_environment_var(envp, "PWD", &PWD) != SUCCESS)
		return (MALLOC_FAIL);
	if (find_environment_var(envp, "OLDPW", &OLDPWD) != SUCCESS)
		return (MALLOC_FAIL);
	if (!cmd)
		return (NO_INPUT);
	if (!cmd[1] || (cmd[1][0] == '~' && !cmd[2]))
		go_home(PWD, OLDPWD);
	else if (cmd[1][0] == '-' && !cmd[2])
		go_prev(PWD, OLDPWD);
	//else if ()
	//update_env();
	return (SUCCEED);
}


//// must be a checker that checks the number of input
//int ft_cd(char *path, t_address add_list)
//{
//	char *current_dir;
//	char *temp;
//	char *joined;

//	current_dir = getcwd(NULL, 0);
//	if (!current_dir)
//		return (perror("getcwd fail"), -1);
//	if (path[0] != '/')
//	{
//		joined = ft_strputjoin(current_dir, path, '/');
//		if (!joined)
//		{
//			free(joined);
//			return (-1);
//		}
//		path = joined;
//	}
//	if (chdir(path) != 0)
//		return (perror("No such file or directory."), -1);
//	if (add_list.prev)
//        add_list.prev->address = current_dir;
//    add_list.address = ft_strdup(path);
//	return (0);
//}

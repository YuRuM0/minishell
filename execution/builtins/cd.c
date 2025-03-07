/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:46:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/03/07 15:18:21 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_strputjoin(char *src1, char *src2, char c, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src1[i])
	{
		dst[j] = src1[i];
		i++;
		j++;
	}
	dst[j] = c;
	j++;
	i = 0;


	while (src2[i])
	{
		dst[j] = src2[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

int	relative(char **args, t_env *env)
{
	char	*pwd;
	char	*new_path;
	int		i;
	char	*cwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	new_path = malloc((ft_strlen(pwd) + ft_strlen(args[1]) + 2) * sizeof(char));
	if (!new_path)
		return (-1);
	new_path = ft_strputjoin(pwd, args[1], '/', new_path);
	free(pwd);
	if (chdir(new_path) == -1)
		return (-1);
	cwd = get_cwd(NULL, 0); //why this arg? yet to read about it...
	ft_env_update(env, "PWD", cwd);
	free(cwd);
	free(new_path);
	return (0);
}


int	cd(char **args , t_env *env)
{
	char	*home;
	char	*pwd;
	char	*cwd;

	if (!args[1]) //if empty bring it home
	{
		home = getenv("HOME");
		if (!home)
			return (-1);
		chdir(home);
		return (0);
	}
	else if (args[1][0] != '/') //relative
		relative(args, env);
	else
	{
		chdir(args[1]);
		if (chdir(args[1]) == -1)
			return (-1);
		cwd = get_cwd(NULL, 0); //why this arg? yet to read about it...
		ft_env_update(env, "PWD", cwd);
		free(cwd);
	}
	return (0);
}

//int main(void)
//{
//	char **args;

//	args = malloc(5 * sizeof(char*));
//	args[0] = "echo";
//	args[1] = "cd.c";
//	cd(args);
//	free(args);

//	return (0);
//}

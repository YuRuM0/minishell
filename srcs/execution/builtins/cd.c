/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:46:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/03/14 18:57:38 by yulpark          ###   ########.fr       */
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



int ft_cd(int ac, char *av[])
{
	if (ac > 1)
		return (-1);
	if (!av[1] || av[1] == '~')
	{
		//call home
	}
	else if (av[1] == '-')
	{
		//get OLPWD env variable
		//if not found print error,return
		//if found
			//change the directory to OLDPWD using chdir
			//print the new directory to STDOUT using ft_putnbr typea func
			//return
	}
	else
	{
		//1. check if the directory exists
		//2. if directory exists
			// change directory using chdir
			// if fails, check if the path is a directory using opendir

		// get the new working directory using getcwd
		// update pwd and oldpwd using change_pwd_value
	}
}

//int main(int ac, char *av[], char **env)
//{
//	char *pwd_before;
//	char *pwd;

//	pwd_before = getcwd(NULL, 0);
//	printf("%s\n", pwd_before);
//	cd(av, env);
//	pwd = getcwd(NULL, 0);
//	printf("%s\n", pwd);
//	return (0);
//}

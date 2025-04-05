/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:31:20 by yuleumpark        #+#    #+#             */
/*   Updated: 2025/04/05 18:31:29 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//char *getcwd(char *buf, size_t size);

int pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

//int main(void)
//{
//	char **args;
//	args = malloc(5 * sizeof(char*));
//	args[0] = "pwd";
//	pwd(args);
//	free(args);
//	return (0);
//}

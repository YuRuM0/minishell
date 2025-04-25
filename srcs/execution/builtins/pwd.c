/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:31:20 by yuleumpark        #+#    #+#             */
/*   Updated: 2025/04/25 18:56:54 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//char *getcwd(char *buf, size_t size);

t_exec_error	pwd(char **cmd)
{
	char	*pwd;

	if (cmd[0] && cmd[1])
		return (error_msg("cd: Too many arguments\n"), ERROR);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ERROR);
	printf("%s\n", pwd);
	free(pwd);
	return (SUCCEED);
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

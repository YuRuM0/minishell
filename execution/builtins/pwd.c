/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuleumpark <yuleumpark@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:31:20 by yuleumpark        #+#    #+#             */
/*   Updated: 2025/03/06 00:05:08 by yuleumpark       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

//char *getcwd(char *buf, size_t size);

int pwd(char **args)
{
	char *pwd;
	
	(void) **args;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
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
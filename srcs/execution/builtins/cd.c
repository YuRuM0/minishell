/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:46:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/11 18:37:33 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//must change so that the dir change is applied

t_exec_error	ft_cd(char **cmd, t_env_var **envp)
{
	t_env_var	*PWD;
	t_env_var	*OLDPWD;

	if (input_counter(cmd) != SUCCEED)
		return (INVALID_INPUT);
	PWD = ft_find_env(*envp, "PWD");
	OLDPWD = ft_find_env(*envp, "OLDPWD");
	if (!cmd)
		return (NO_INPUT);
	if (cmd[1][0] == '.')
		ft_cd_dots(cmd[1], *envp, PWD);
	else if (!cmd[1] || cmd[1][0] == '~' || \
		 (cmd[1][0] == '-' && cmd[1][1] && cmd[1][1] == '-'))
		go_home(envp, PWD);
	else if (cmd[1][0] == '-')
		go_prev(envp, PWD, OLDPWD);
	else if (cmd[1][0] != '/' && cmd[1][0] != '.')
		relative_path(cmd[1], envp, PWD);
	else if (cmd[1][0] == '/')
		absolute_path(cmd[1], envp, PWD);
	return (SUCCEED);
}

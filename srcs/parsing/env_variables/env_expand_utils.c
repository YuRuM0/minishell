/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:04:52 by flima             #+#    #+#             */
/*   Updated: 2025/04/22 18:54:09 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_pars_err	find_environment_var(t_env_var *envp, char *var_name, \
	char **environ_var)
{
	size_t		len;

	*environ_var = NULL;
	len = ft_strlen(var_name);
	while (envp)
	{
		if ((ft_strncmp(envp->variable, var_name, len)) == 0)
		{
			*environ_var = ft_strdup(envp->variable);
			if (*environ_var == NULL && errno == ENOMEM)
				return (ERROR_MEM_ALLOC);
			break ;
		}
		envp = envp->next;
	}
	if (*environ_var == NULL)
		*environ_var = ft_strdup("");
	if (*environ_var == NULL && errno == ENOMEM)
		return (ERROR_MEM_ALLOC);
	return (SUCCESS);
}

t_pars_err	get_environ_var_value(char **environ_var, char *var_name)
{
	char	*tmp_name;
	char	*tmp_var;

	tmp_name = ft_strjoin(var_name, "=");
	if (tmp_name == NULL && errno == ENOMEM)
		return (ERROR_MEM_ALLOC);
	tmp_var = ft_substr(*environ_var, ft_strlen(tmp_name), ft_strlen(*environ_var)-ft_strlen(tmp_name));
	free(tmp_name);
	if (tmp_var == NULL && errno == ENOMEM)
		return (ERROR_MEM_ALLOC);
	free(*environ_var);
	*environ_var = tmp_var;
	return (SUCCESS);
}

t_pars_err	expand_environ_var(t_env_var *envp, char *var_name, \
	char **environ_var)
{
	t_pars_err	status;

	status = find_environment_var(envp, var_name, environ_var);
	if (status == ERROR_MEM_ALLOC)
		return (ERROR_MEM_ALLOC);
	if (*environ_var[0] == '\0')
		return (SUCCESS);
	status = get_environ_var_value(environ_var, var_name);
	if (status == ERROR_MEM_ALLOC)
		return (ERROR_MEM_ALLOC);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:00:31 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/11 18:07:15 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_env_var	*ft_find_env(t_env_var *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->variable, key, ft_strlen(key)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_env_update(t_env_var *env, char *name, char *path)
{
	t_env_var	*temp;

	temp = ft_find_env(env, name);
	if (temp)
	{
		free(temp->variable);
		temp->variable = ft_strdup(path); //malloc
		if (!temp->variable)
			return (-1);
	}
	return (0);
}

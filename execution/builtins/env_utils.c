/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:00:31 by yuleumpark        #+#    #+#             */
/*   Updated: 2025/03/07 15:47:51 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_env *ft_find_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return env;
		env = env->next;
	}
	return NULL;
}


int ft_env_update(t_env *env, char *name, char *path)
{
	t_env *temp;

	temp = find_env(env, name);
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(path); //malloc
		if (!temp->value)
			return (-1);
	}
	return (0);
}

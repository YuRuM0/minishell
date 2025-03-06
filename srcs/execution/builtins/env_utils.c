/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuleumpark <yuleumpark@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:00:31 by yuleumpark        #+#    #+#             */
/*   Updated: 2025/03/06 00:11:38 by yuleumpark       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

//t_env *ft_find_env(t_env *env, char *key)
//{
//	while (env)
//	{
//		if (ft_strcmp(env->key, key) == 0)
//			return env;
//		env = env->next;
//	}
//	return NULL;=
//}

//int ft_addfront_env(t_env **env, char *key, char *value)
//{
//	t_env *new_env;

//	new_env = malloc(sizeof(t_env));
//	if (!new_env)
//		return (-1);
//	new_env->key = ft_strdup(key);
//	new_env->value = ft_strdup(value);
//	if (!new_env->key || !new_env->value)
//	{
//		free(new_env->key);
//		free(new_env->value);
//		free(new_env);
//		return (-1);
//	}
//	new_env->next = *env;
//	*env = new_env;
//	return (0);
//}

//int ft_env_update(t_env *env, char *key, char *value)
//{
//	t_env *temp_env
	
//	temp_env = find_env(env, key);
//	if (temp_env) 
//	{
//		free(temp_env->value);
//		temp_env->value = ft_strdup(value);
//		if (!temp_env->value)
//			return (-1);
//	} 
//	else 
//	{
//		if (add_env(env, key, value) == -1)
//			return (-1);
//	}
//	return (0);
//}
//value = get_cwd(NULL, 0);
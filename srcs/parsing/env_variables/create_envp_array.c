/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:54:42 by flima             #+#    #+#             */
/*   Updated: 2025/04/19 17:13:11 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

static int	count_envp_vars(t_env_var *envp)
{
	int	i;

	i = 0;
	while (envp != NULL)
	{
		i++;
		envp = envp->next;
	}
	return (i);
}


void	create_envp_array(t_main_data *data, t_env_var *envp)
{
	char **envp_array;
	int	i;
	
	i = 0;
	envp_array = ft_calloc(count_envp_vars(envp) + 1, sizeof(char **));
	if (envp_array == NULL)
		status_error(data, ERROR_MEM_ALLOC);
	while (envp != NULL)
	{
		envp_array[i] = ft_strdup(envp->variable);
		if (envp_array[i] == NULL)
		{
			free_double(envp_array);
			status_error(data, ERROR_MEM_ALLOC);
		}
		i++;
		envp =  envp->next;
	}
	envp_array[i] = NULL;
	data->envp_array = envp_array;
}
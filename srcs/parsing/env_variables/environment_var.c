/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:29:38 by flima             #+#    #+#             */
/*   Updated: 2025/03/29 21:54:48 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	duplicate_env_var(t_main_data *data, char **envp)
{
	int			i;
	t_env_var	*new_node;

	i = -1;
	while (envp[++i])
	{
		new_node = add_new_var();
		if (new_node == NULL)
			status_error(data, ERROR_MEM_ALLOC);
		new_node->variable = ft_strdup(envp[i]);
		if (new_node == NULL)
			status_error(data, ERROR_MEM_ALLOC);
		add_var_back(&data->env_vars, new_node);
	}
}

char	*find_environment_var(t_main_data *data, char *var_name)
{
	size_t		len;
	t_env_var	*current;
	char 		*environ_var;
	
	current = data->env_vars;
	environ_var = NULL;
	len = ft_strlen(var_name);
	while (current)
	{
		if ((ft_strncmp(current->variable, var_name, len)) == 0)
		{
			environ_var = ft_strdup(current->variable);
			break;
		}
		current = current->next;
	}
	return (environ_var);
}

t_pars_err	get_environ_var_value(char **environ_var, char *var_name)
{
	char	*tmp_name;
	char	*tmp_var;
	
	tmp_name = ft_strjoin(var_name, "=");
	if (tmp_name == NULL && errno == ENOMEM)
		return (ERROR_MEM_ALLOC);
	tmp_var = ft_strtrim(*environ_var, tmp_name);
	free(tmp_name);
	if (tmp_var == NULL && errno == ENOMEM)
		return (ERROR_MEM_ALLOC);
	free(*environ_var);
	*environ_var = tmp_var;
	return (SUCCESS);
}

// var_name should be created using malloc because this function use free in case of error
char	*expand_environ_var(t_main_data *data, char *var_name)
{
	char		*environ_var;
	t_pars_err	status;
	
	environ_var = find_environment_var(data, var_name);
	// if (environ_var == NULL && errno == ENOMEM)
	// {
	// 	//TO DO
	// }	//maloc		/malloc
	if (environ_var == NULL)
		return (environ_var);
	status = get_environ_var_value(&environ_var, var_name);
	(void)status;
	return(environ_var);
}
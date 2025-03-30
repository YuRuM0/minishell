/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:29:38 by flima             #+#    #+#             */
/*   Updated: 2025/03/30 18:38:02 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_pars_err get_environ_var_value(char **environ_var, char *var_name)
{
	char *tmp_name;
	char *tmp_var;

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

char *expand_environ_var(t_main_data *data, char *var_name)
{
	char *environ_var;
	t_pars_err status;

	// check if var_name is $?
	environ_var = find_environment_var(data, var_name);
	if (environ_var == NULL && errno == ENOMEM)
	{
		free(var_name);
		status_error(data, ERROR_MEM_ALLOC);
	}
	if (environ_var[0] == '\0')
		return (environ_var);
	status = get_environ_var_value(&environ_var, var_name);
	if (status == ERROR_MEM_ALLOC)
	{
		free(environ_var);
		free(var_name);
		status_error(data, ERROR_MEM_ALLOC);
	}
	return (environ_var);
}

char *extract_var_name(char *str)
{
	char *var_name;
	int len;

	len = 0;
	while (str[len] && (str[len] != ' ' || str[len] == '?'))
		len++;
	if (str[len] == '?')
		len++;
	var_name = ft_substr(str, 0, len);
	return (var_name);
}

char *append_expanded_var(char	**expand, char *var_value, int *i, \
		char *var_name)
{
	char *new_expand;
	int len;

	len = ft_strlen(*expand) + ft_strlen(var_value) - ft_strlen(var_name) - 1;
	new_expand = ft_calloc(len + 1, sizeof(char));
	if (new_expand == NULL && errno == ENOMEM)
		return (NULL);
	ft_strlcpy(new_expand, *expand, *i - 1);
	ft_strlcat(new_expand, var_value, len);
	ft_strlcat(new_expand, *expand + *i + ft_strlen(var_name), len);
	(*i) += ft_strlen(var_value - 1);
	free(var_value);
	free(*expand);
	free(var_name);
	*expand = new_expand;
	return (new_expand);
}

char *expand_env_instr(t_main_data *data, char *expand)
{
	char *var_value;
	char *var_name;
	int i;

	i = 0;
	while (expand[i])
	{
		if (expand[i] == '$' && expand[i + 1] && (ft_isalnum(expand[i + 1])\
			|| expand[i + 1] == '?'))
		{
			var_name = extract_var_name(expand + i + 1);
			// if (var_name == NULL)
			// 	return (ERROR_MEM_ALLOC);
			var_value = expand_environ_var(data, var_name);
			append_expanded_var(&expand, var_value, &i, var_name);
			// if (var_value == NULL)
			// {
			// 	free(var_name);
			// 	free(var_value);
			// 	return (ERROR_MEM_ALLOC);
			// }
		}
		else if (expand[i] == '$' && expand[i + 1] != ' ')
		{
			var_name = extract_var_name(expand + i + 1);
			// if (var_name == NULL)
			// 	return (ERROR_MEM_ALLOC);
			append_expanded_var(&expand, var_name + 1, &i, var_name);
			// if (var_name == NULL)
			// {
			// 	free(var_name);
			// 	return (ERROR_MEM_ALLOC);
			// }
		}
		else
			i++;
	}
	return (expand);
}

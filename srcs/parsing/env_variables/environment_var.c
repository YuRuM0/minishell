/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:29:38 by flima             #+#    #+#             */
/*   Updated: 2025/04/08 16:08:23 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

static t_pars_err	extract_var_name(char *str, char **var_name)
{
	int	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	if (str[len] == '?' && len == 0)
		len++;
	*var_name = ft_substr(str, 0, len);
	if (*var_name == NULL && errno == ENOMEM)
		return (ERROR_MEM_ALLOC);
	return (SUCCESS);
}

static t_pars_err	append_expanded_var(char **expand, char *var_value, int *i, \
		char *var_name)
{
	char	*new_expand;
	int		len;

	len = ft_strlen(*expand) + ft_strlen(var_value) - ft_strlen(var_name);
	new_expand = ft_calloc(len + 1, sizeof(char));
	if (new_expand == NULL && errno == ENOMEM)
		return (ERROR_MEM_ALLOC);
	ft_strlcpy(new_expand, *expand, *i + 1);
	ft_strlcat(new_expand, var_value, len);
	ft_strlcat(new_expand, *expand + (*i + ft_strlen(var_name) + 1), len);
	(*i) += ft_strlen(var_value) -1;
	if (*i == -1)
		(*i) = 0;
	free(*expand);
	*expand = new_expand;
	return (SUCCESS);
}

static t_pars_err	expand_valid_env(t_env_var *envp, char **expand, int *i)
{
	char		*var_value;
	char		*var_name;
	t_pars_err	status;

	status = extract_var_name(*expand + *i + 1, &var_name);
	if (status == ERROR_MEM_ALLOC)
		return (ERROR_MEM_ALLOC);
	status = expand_environ_var(envp, var_name, &var_value);
	if (status == ERROR_MEM_ALLOC)
		return (free(var_name), ERROR_MEM_ALLOC);
	status = append_expanded_var(expand, var_value, i, var_name);
	if (status == ERROR_MEM_ALLOC)
	{
		free(var_name);
		free(var_value);
		return (ERROR_MEM_ALLOC);
	}
	free(var_name);
	free(var_value);
	return (SUCCESS);
}

static t_pars_err	expand_invalid_env(char **expand, int *i)
{
	char		*var_name;
	t_pars_err	status;

	status = extract_var_name(*expand + *i + 1, &var_name);
	if (status == ERROR_MEM_ALLOC)
		return (ERROR_MEM_ALLOC);
	status = append_expanded_var(expand, var_name + 1, i, var_name);
	if (status == ERROR_MEM_ALLOC)
	{
		free(var_name);
		return (ERROR_MEM_ALLOC);
	}
	return (SUCCESS);
}

t_pars_err	expand_env_instr(t_env_var *envp, char **expand)
{
	int			i;
	t_pars_err	status;

	i = 0;
	while ((*expand)[i])
	{
		if ((*expand)[i] == '$' && (*expand)[i + 1] && \
		(ft_isalpha((*expand)[i + 1]) || (*expand)[i + 1] == '?' || \
		(*expand)[i + 1] == '_'))
		{
			status = expand_valid_env(envp, expand, &i);
			if (status == ERROR_MEM_ALLOC)
				return (ERROR_MEM_ALLOC);
		}
		else if ((*expand)[i] == '$' && (*expand)[i + 1] != ' ')
		{
			status = expand_invalid_env(expand, &i);
			if (status == ERROR_MEM_ALLOC)
				return (ERROR_MEM_ALLOC);
		}
		else
			i++;
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:50:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/27 18:31:40 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_var_name(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (NULL);
	while (arg[i] && (arg[i] != '=' && arg[i] != '+'))
		i++;
	return (ft_substr(arg, 0, i));
}

int	input_checker(char *input)
{
	int	i;

	if (input[0] && (ft_isalpha(input[0]) == 0 && input[0] != '_'))
		return (-1);
	i = 1;
	while (input[0] && input[i] != '\0')
	{
		if (input[i] == '+' || input[i] == '/')
			return (-1);
		i++;
	}
	return (0);
}

int	create_new_var(char *arg, t_env_var **envp, t_main_data *data)
{
	t_env_var	*new_var;

	new_var = add_new_var();
	if (!new_var)
		return (error_msg(NULL), -1);
	add_var_back(envp, new_var);
	if (ft_strchr(arg, '=') == NULL)
		new_var->is_exported = 0;
	if (ft_add_key_val(envp, arg, data) != 0)
		return (-1);
	return (0);
}

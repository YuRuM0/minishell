/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:58:46 by yuleumpark        #+#    #+#             */
/*   Updated: 2025/03/29 20:57:38 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// must check for the input
// can't start with a num
// no - allowed
// can start with _
// can contain underscores
// = only appears once, after the identifier name

int input_checker(char *input)
{
	int i;
	int equal_counter;

	i = 1;
	if (input && !(ft_isalpha(input[0]) == 1 || input[0] == '_'))
		return (-1);
	equal_counter = 0;
	while (input[i])
	{
		if (input[i] == '=')
			equal_counter++;
		if (!(input[i] == '_' || ft_isalnum(input[i]) == 1))
			return (-1);
		i++;
	}
	if (equal_counter <= 1)
		return (0);
	return (-1);
}

//int export_noarg(char **args)
//{
//	;
//}

char *get_key(char *arg)
{
	int i;
	char *result;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] != '=') //if no =
		return (NULL);
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, arg, i + 1);
	return (result);
}

char *get_value(char *arg)
{
	int i;
	char *result;

	i = 0;
	if (!arg)
		return (NULL);
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg) //incase no = 
		return (NULL);
	i++;
	result = malloc(sizeof(char) * ft_strlen(arg + i) + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, &arg[i], ft_strlen(arg + i) + 1);
	return (result);
}

// only handles one arg at a time from the long list with many args
int export_arg(char *arg, t_varlist ** var_list)
{
	int i;
	char *key;
	char *value;

	i = 1;
	if (input_checker(arg) == -1)
		return (perror("Export: Invalid Input"), -1);
	key = get_key(arg);
	if (!key)
		return (perror("Export: Malloc Error"), -1);
	value = get_value(arg); // if this is NULL then only add key to the node
	
}

int main()
{
	char *input3 = "VAR=VALUE";
	char *key;
	char *val;

	key = get_key(input3);
	val = get_value(input3);
	printf("%s\n", key);
	printf("%s", val);
}
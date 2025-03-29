/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:25:58 by yulpark           #+#    #+#             */
/*   Updated: 2025/03/29 21:26:16 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
void	add_key_value_node(t_varlist *lst, char *key, char *value)
{
	t_varlist	*temp;

	temp = malloc(sizeof(t_varlist));
    if (!temp)
        return;
	temp->key = ft_strdup(key);
	temp->content = NULL;
	if (value)
		temp->content = ft_strdup(value);
	temp->next = NULL;
	if (lst == NULL)
	{
		temp->prev = NULL;
		lst = temp;
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = temp;
	temp->prev = lst;
}
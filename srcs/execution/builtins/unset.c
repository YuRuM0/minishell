/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:41:41 by yulpark           #+#    #+#             */
/*   Updated: 2025/03/20 19:10:57 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
//given that the copy of the env_var is the input
//but as long as this case is going it must remember that the var is removed?
//check if after deleting the variable the echo works or not. It shouldn't

//ref
//typedef struct s_varlist
//{
//	char *key;
//	char *content;
//	char *next;
//}	t_env;

static void ft_delete_node(t_varlist *current, t_varlist *begin)
{
	if (current->prev == NULL)
		begin = current->next;
	else
	{
		current->prev->next = current->next;
		current = current->next;
	}
}

//handling if the input is more than 2 (unset _ )
int fd_unset(char **args, t_varlist *listinho)
{
	int i;
	t_varlist *cur_node;

	i = 0;
	cur_node = listinho;
	if (!args[1])
		return (0);
	while (cur_node != NULL)
	{
		if (ft_strncmp(cur_node->key, args[1], ft_strlen(args[1])) == 0)
			ft_delete_node(cur_node, listinho);
		else
			cur_node = cur_node->next;
	}
	return (0);
}

int main()
{
	t_varlist *variables;

	variables = malloc(sizeof(t_varlist));
	if (!variables)
		return (0);
	variables->prev = NULL;
	variables->key = ft_strdup("HOME");
	variables->content = ft_strdup("/home/yulpark");
	variables->next = malloc(sizeof(t_varlist));
	variables->next->prev = variables;
	variables->next->key = ft_strdup("PATH");
	variables->next->content = ft_strdup("/blablabla");
	variables->next->next = NULL;
	char **args;
	args = malloc(sizeof(char*) * 3);
	args[0] = "unset";
	args[1] = "PATH";
	args[2] = NULL;
	fd_unset(args, variables);
	while (variables->key)
	{
		printf("%s", variables->key);
		variables = variables->next;
	}
	return (0);
}

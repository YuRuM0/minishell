/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:41:41 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/23 15:46:02 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
//given that the copy of the env_var is the input
//but as long as this case is going it must remember that the var is removed?
//check if after deleting the variable the echo works or not. It shouldn't

void	ft_delete_node(t_env_var **envp, t_env_var *head, int i)
{
	t_env_var	*temp;

	if (i == 1)
	{
		*envp = head->next;
		head->next = NULL;
		free(head->variable);
		free(head);
	}
	else
	{
		temp = head->next;
		head->next = head->next->next;
		temp->next = NULL;
		free(temp->variable);
		free(temp);
	}
}

//handling if the input is more than 2 (unset _ )
//envp here: copied version of linked list
t_exec_error	ft_unset(char **args, t_env_var **envp)
{
	t_env_var	*head;

	if (!args[1] || !envp)
		return (SUCCEED);
	head = *envp;
	if (ft_strncmp(head->variable, args[1], ft_strlen(args[1])) == 0)
	{
		ft_delete_node(envp, head, 1);
		return (SUCCEED);
	}
	while (head->next)
	{
		if (ft_strncmp(head->next->variable, args[1], \
			ft_strlen(args[1])) == 0)
		{
			ft_delete_node(envp, head, 0);
			return (SUCCEED);
		}
		head = head->next;
	}
	return (SUCCEED);
}

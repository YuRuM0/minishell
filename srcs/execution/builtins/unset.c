/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:41:41 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/27 16:11:46 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
//given that the copy of the env_var is the input
//but as long as this case is going it must remember that the var is removed?
//check if after deleting the variable the echo works or not. It shouldn't

static void	remove_next_env(t_env_var **current)
{
	t_env_var	*tmp;

	tmp = (*current)->next;
	(*current)->next = (*current)->next->next;
	tmp->next = NULL;
	free(tmp->variable);
}

//handling if the input is more than 2 (unset _ )
//envp here: copied version of linked list
t_exec_error	ft_unset(char **args, t_env_var **envp)
{
	t_env_var	*head;

	if (!args[1] || !envp)
		return (SUCCEED);
	head = *envp;
	while (head->next)
	{
		if (ft_strncmp(head->next->variable, args[1], \
			ft_strlen(args[1])) == 0)
		{
			remove_next_env(&head);
			return (SUCCEED);
		}
		head = head->next;
	}
	return (SUCCEED);
}

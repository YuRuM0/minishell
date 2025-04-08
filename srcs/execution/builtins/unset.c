/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:41:41 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/08 15:05:14 by yulpark          ###   ########.fr       */
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
int	ft_unset(char **args, t_env_var **envp)
{
	t_env_var	*head;

	if (!args[1] || !envp)
		return (0);
	head = *envp;
	if (ft_strncmp(head->variable, args[1], ft_strlen(args[1])) == 0)
	{
		ft_delete_node(envp, head, 1);
		return (0);
	}
	while (head->next)
	{
		if (ft_strncmp(head->next->variable, args[1], ft_strlen(args[1])) == 0) //include null
		{
			ft_delete_node(envp, head, 0);
			return (0);
		}
		head = head->next;
	}
	return (0);
}

//t_env_var  *create_node(char *key)
//{
//    t_env_var *node = malloc(sizeof(t_env_var));
//    node->variable = strdup(key);
//    node->next = NULL;
//    return node;
//}

//void print_list(t_env_var *list)
//{
//    printf("Current list:\n");
//    while (list)
//    {
//        printf("%s\n", list->variable);
//        list = list->next;
//    }
//}

//int main()
//{
//    t_env_var *list = NULL;
//    t_env_var *node1 = create_node("VAR1=value1");
//    t_env_var *node2 = create_node("VAR2=value2");
//    t_env_var *node3 = create_node("VAR3=value3");
//    node1->next = node2;
//    node2->next = node3;
//    list = node1;
//    printf("Initial list:\n");
//    print_list(list);

//    char *args1[] = {"unset", "VAR2"};
//    fd_unset(args1, &list);
//    printf("Deleting VAR2:\n");
//    print_list(list);

//    char *args2[] = {"unset", "VAR1", NULL};
//    fd_unset(args2, &list);
//    printf("Deleting VAR1:\n");
//    print_list(list);

//    char *args4[] = {"unset", "NONEXISTENT", NULL};
//    fd_unset(args4, &list);
//    printf("After deleting NONEXISTENT (empty list):\n");
//    print_list(list);
//    return 0;
//}

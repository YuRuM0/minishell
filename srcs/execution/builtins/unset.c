/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:41:41 by yulpark           #+#    #+#             */
/*   Updated: 2025/03/29 20:41:21 by yulpark          ###   ########.fr       */
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


void ft_delete_node(t_varlist **begin, t_varlist *current)
{
    if (!current)
        return;
    if (current->prev == NULL) // Deleting the first node
        *begin = current->next;
    else
        current->prev->next = current->next;
    if (current->next != NULL) // Avoid accessing NULL->prev
        current->next->prev = current->prev;
    free(current->key);
    free(current->content);
    free(current);
}

//handling if the input is more than 2 (unset _ )
int fd_unset(char **args, t_varlist **listinho)
{
	t_varlist *cur_node;
	t_varlist *next_node;
	
    if (!args[1] || !*listinho)
        return (0);
    while (cur_node)
    {
        next_node = cur_node->next;
        if (strncmp(cur_node->key, args[1], strlen(args[1]) + 1) == 0) //include null
            ft_delete_node(listinho, cur_node);
        cur_node = next_node;
    }
    return (0);
}

//t_varlist *create_node(char *key, char *content)
//{
//    t_varlist *node = malloc(sizeof(t_varlist));
//    node->key = strdup(key);
//    node->content = strdup(content);
//    node->prev = NULL;
//    node->next = NULL;
//    return node;
//}

//void print_list(t_varlist *list)
//{
//    printf("Current list:\n");
//    while (list)
//    {
//        printf("%s:%s\n", list->key, list->content);
//        list = list->next;
//    }
//}

//int main()
//{
//    t_varlist *list = NULL;
//    t_varlist *node1 = create_node("VAR1", "value1");
//    t_varlist *node2 = create_node("VAR2", "value2");
//    t_varlist *node3 = create_node("VAR3", "value3");
//    node1->next = node2;
//    node2->prev = node1;
//    node2->next = node3;
//    node3->prev = node2;
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
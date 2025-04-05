/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:46:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/05 17:46:42 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*ft_strputjoin(char *src1, char *src2, char c)
{
	int	i;
	int	j;
	char *dst;

	i = 0;
	j = 0;
	dst = malloc(ft_strlen(src1) + ft_strlen(src2) + 2);
    if (!dst)
         return NULL;
	if (!src1 || !src2)
		return (0);
	while (src1 && src1[i])
	{
		dst[j] = src1[i];
		i++;
		j++;
	}
	dst[j] = c;
	j++;
	i = 0;
	while (src2 && src2[i])
	{
		dst[j] = src2[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

//static t_address *ft_init_addlist(void)
//{
//    t_address *current;
//    t_address *previous;

//    current = malloc(sizeof(t_address));
//    if (!current)
//        return NULL;
//    previous = malloc(sizeof(t_address));
//    if (!previous)
//    {
//        free(current);
//        return NULL;
//    }
//    current->address = NULL;
//    current->prev = previous;
//    current->next = NULL;
//    previous->address = NULL;
//    previous->prev = NULL;
//    previous->next = current;

//    return current;
//}

// must be a checker that checks the number of input
int ft_cd(char *path, t_address add_list)
{
	char *current_dir;
	char *temp;
	char *joined;

	if (!path || path[0] == '~')
	{
		path = getenv("HOME");
		if (!path)
			return (perror("Failed to get path of home"), -1);
		chdir(path);
	}
	else if (path[0] == '-' && path[1] == '\0')
	{
		if (!add_list.prev->address)
			return (ft_putstr_fd(getcwd(NULL, 0), 1), 0);
		else
		{
			temp = ft_strdup(add_list.prev->address);
			if (!temp)
				return (-1);
			add_list.prev->address = add_list.address;
			chdir(add_list.address);
			add_list.address = temp;
			ft_putstr_fd(getcwd(NULL, 0), 1);
			return (0);
		}
	}
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (perror("getcwd fail"), -1);
	if (path[0] != '/')
	{
		joined = ft_strputjoin(current_dir, path, '/');
		if (!joined)
		{
			free(joined);
			return (-1);
		}
		path = joined;
	}
	if (chdir(path) != 0)
		return (perror("No such file or directory."), -1);
	if (add_list.prev)
        add_list.prev->address = current_dir;
    add_list.address = ft_strdup(path);
	return (0);
}

//void test_cd_dash(void)
//{
//    printf("\n===== Testing cd - functionality =====\n");

//    t_address *add_list = ft_init_addlist();
//    char *start_dir = getcwd(NULL, 0);
//    printf("Starting directory: %s\n", start_dir);

//    //// First cd to a different directory
//    //char *first_dir = "/tmp";  // This should exist on most systems
//    //printf("\n1. Changing to first directory: %s\n", first_dir);
//    //add_list->address = ft_strdup(start_dir);
//    //add_list->prev->address = NULL;  // No previous directory yet

//    //int result1 = ft_cd(first_dir, *add_list);
//    //printf("ft_cd result: %d\n", result1);
//    //printf("Current directory: %s\n", getcwd(NULL, 0));
//    //printf("Previous directory: %s\n", add_list->prev->address);

//    // Now cd to another directory
//    char *second_dir = "/";  // Root directory
//    printf("\n2. Changing to second directory: %s\n", second_dir);

//    int result2 = ft_cd(second_dir, *add_list);
//    printf("ft_cd result: %d\n", result2);
//    printf("Current directory: %s\n", getcwd(NULL, 0));
//    printf("Previous directory: %s\n", add_list->prev->address);

//    // Now test the cd - functionality
//    printf("\n3. Testing cd -\n");

//    int result3 = ft_cd("-", *add_list);
//    printf("ft_cd(\"-\") result: %d\n", result3);
//    printf("Current directory: %s\n", getcwd(NULL, 0));
//    printf("Previous directory: %s\n", add_list->prev->address);

//    // Test another cd - to swap back
//    printf("\n4. Testing second cd -\n");

//    int result4 = ft_cd("-", *add_list);
//    printf("ft_cd(\"-\") result: %d\n", result4);
//    printf("Current directory: %s\n", getcwd(NULL, 0));
//    printf("Previous directory: %s\n", add_list->prev->address);

//    // Cleanup
//    free(start_dir);

//    // Free the address list structures
//    if (add_list->prev)
//    {
//        free(add_list->prev->address);
//        free(add_list->prev);
//    }
//    free(add_list->address);
//    free(add_list);
//}

//int main(void)
//{
//    //test_ft_cd();
//	 test_cd_dash();
//    printf("\n===== All tests completed =====\n");
//    return (0);
//}

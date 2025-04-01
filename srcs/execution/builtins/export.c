/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:58:46 by yuleumpark        #+#    #+#             */
/*   Updated: 2025/04/01 23:57:24 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
//need to change because we ain't printing envp but export variables

// must check for the input
// can't start with a num
// no - allowed
// can start with _
// can contain underscores
// = only appears once, after the identifier name

static int input_checker(char *input)
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
		else if (!(input[i] == '_' || ft_isalnum(input[i]) == 1))
			return (-1);
		i++;
	}
	if (equal_counter <= 1)
		return (0);
	return (-1);
}

// if the args[1] is empty; "export"
int export_noarg(t_env_var *envp)
{
	char *to_print;
	int i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp)
	{
		//to_print = ft_strjoin("declare -x", envp->variable);
		//ft_printf("%s\n", to_print);
		//envp = envp->next;
		write(1, "declare -x ", 12);
		while (envp->variable[i])
		{
			write(1, &envp->variable[i], 1);
			if (envp->variable[i] == '=')
				write(1, "\"", 1);
			i++;
		}
		write(1, "\"\n", 2);
		i = 0;
		envp = envp->next;
	}
	return (0);
}

int	ft_add_key_val(t_env_var **head, char *keyvalue)
{
	t_env_var	*temp;

	if (*head == NULL)
		return (perror("Export: empty environment var"), -1);
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->variable = ft_strdup(keyvalue);
		free(keyvalue);
		return (0);
	}
}

// only handles one arg at a time from the long list with many args
// envp - contains all env variables, coming from duplicate_env_var (?)

int export_arg(char *arg, t_env_var **envp)
{
	t_env_var *new_var;
	int j;
	t_env_var *head;

	j = 0;
	head = *envp;
	if (input_checker(arg) == -1)
		return (-1);
	while (head)
	{
		while (head->variable[j] != '=')
			j++;
		if (ft_strncmp(head->variable, arg, j + 1) == 0)
		{
			head->variable = ft_strdup(arg);
			return (0);
		}
		head = head->next;
	}
	new_var = add_new_var();
	add_var_back(envp, new_var);
	ft_add_key_val(envp, arg);
	return (0);
}

int export(char **args, t_env_var **envp)
{
	int i;

	if (!args)
		return (perror("Export: no input"), -1);
	if (!args[1])
		return(export_noarg(*envp));
	i = 1;
	while (args[i])
	{
		if (export_arg(args[i], envp) == -1)
			return (perror("Export: Invalid Input"), -1);
		if (export_arg(args[i], envp) == -2)
			return(perror("Export: Malloc Error"), -1);
		else
			i++;
	}
	return (0);
}

//int main()
//{
//	t_env_var *var1 = malloc(sizeof(t_env_var) * 10);
//	t_env_var *var2 = malloc(sizeof(t_env_var) * 10);

//	var1->variable = strdup("var1=VALUE");
//	var2->variable = strdup("var2=VALUE");
//	var1->next = var2;
//	var2->next = NULL;

//	char **arg = malloc(sizeof(char*) * 3);
//	arg[0] = ft_strdup("export");
//	arg[2] = NULL;
//	arg[1] = NULL;
//	export(arg, &var1);
//	while (var1)
//	{
//		printf("%s\n", var1->variable);
//		var1 = var1->next;
//	}
//	return (0);
//}

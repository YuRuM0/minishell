/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:58:46 by yuleumpark        #+#    #+#             */
/*   Updated: 2025/04/08 16:32:46 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
//need to change because we ain't printing envp but export variables

// must check for the input
// can't start with a num
// no - allowed
// can start with _
// can contain underscores
// = only appears once, after the identifier name

// if the args[1] is empty; "export"
static int	export_noarg(t_env_var *envp)
{
	int		i;

	if (!envp)
		return (-1);
	while (envp)
	{
		i = 0;
		if (envp->is_exported != 2)
		{
			write(1, "declare -x ", 12);
			while (envp->variable[i])
			{
				write(1, &envp->variable[i], 1);
				if (envp->variable[i] == '=')
					write(1, "\"", 1);
				i++;
			}
			if (envp->is_exported == 1)
				write(1, "\"", 1);
			write(1, "\n", 1);
		}
		envp = envp->next;
	}
	return (0);
}

int	ft_add_key_val(t_env_var **head, char *keyvalue)
{
	t_env_var	*temp;

	if (*head == NULL)
		return (error_msg("Export: empty environment var"), -1);
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->variable = ft_strdup(keyvalue);
		return (0);
	}
}

// only handles one arg at a time from the long list with many args
// envp - contains all env variables, coming from duplicate_env_var (?)

static char	*replace_or_join_var(char *arg, t_env_var *head, char *name)
{
	char	*temp;

	if (ft_strchr(head->variable, '+') == NULL)
	{
		if (ft_strchr(head->variable, '=') == NULL)
			temp = ft_strjoin(head->variable, &arg[ft_strlen(name) + 1]);
		else
			temp = ft_strjoin(head->variable, &arg[ft_strlen(name) + 2]);
	}
	else
		temp = ft_strdup(arg);
	if (ft_strncmp(arg, name, ft_strlen(name) + 1) == 0)
		head->is_exported = 0;
	else
		head->is_exported = 1;
	free(head->variable);
	free(name);
	return (temp);
}

int	export_arg(char *arg, t_env_var **envp)
{
	t_env_var	*head;
	char		*name;

	if (input_checker(arg) == -1)
		return (-1);
	head = *envp;
	name = get_var_name(arg);
	if (name)
		printf("%s\n", name);
	while (head)
	{
		if (ft_strncmp(head->variable, name, ft_strlen(name)) == 0)
		{
			head->variable = replace_or_join_var(arg, head, name);
			if (!head->variable)
				return (-1);
			return (0);
		}
		head = head->next;
	}
	free(name);
	if (create_new_var(arg, envp) != 0)
		return (-1);
	return (0);
}

int	export(char **args, t_env_var **envp)
{
	int	i;
	int	check;

	if (!args)
		return (error_msg("Export: no input\n"), -1);
	if (!args[1])
		return(export_noarg(*envp));
	i = 1;
	while (args[i])
	{
		check = export_arg(args[i], envp);
		if (check == -1)
			return (error_msg("Export: Invalid Input\n"), -1);
		else if (check == -2)
			return(error_msg(NULL), -1);
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

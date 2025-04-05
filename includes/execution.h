/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:26:53 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/05 18:08:50 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <dirent.h>
#include "minishell.h"
#include "libft.h"
#include "tokenization.h"

//typedef struct s_address
//{
//	char *address;
//	struct s_address *prev;
//	struct s_address *next;
//}	t_address;

typedef struct s_loc{
	char *old_pwd;
	char *pwd;
	char *env;
}	t_loc;


int			distribution(t_main_data *data);

//builtins

//int			ft_cd(char *path, t_address add_list);
int			echo(char **args);
int			env(t_env_var *envp, char **args);
void		ft_exit(char **cmd, t_main_data *data);
int			export_arg(char *arg, t_env_var **envp, int builtchecker);
int			export(char **args, t_env_var **envp);
int			pwd();
int			fd_unset(char **args, t_env_var **envp);

//env_utils
t_env_var	*ft_find_env(t_env_var *env, char *key);
int			ft_env_update(t_env_var *env, char *name, char *path);
int			ft_add_key_val(t_env_var **head, char *keyvalue); //export
void		ft_delete_node(t_env_var **envp, t_env_var *head, int i); //unset
#endif



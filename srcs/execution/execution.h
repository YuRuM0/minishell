/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:26:53 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/04 19:42:05 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <dirent.h>
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include "../../includes/tokenization.h"

typedef struct s_address
{
	char *address;
	struct s_address *prev;
	struct s_address *next;
}	t_address;

typedef struct s_loc{
	char *old_pwd;
	char *pwd;
	char *env;
}	t_loc;

//typedef struct s_varlist
//{
//	char *key;
//	char *content;
//	struct s_varlist *prev;
//	struct s_varlist *next;
//}	t_varlist;




//builtins
void		manage_builtins(char **args, t_env_var *envp, t_address add_list, t_main_data *data);

int			ft_cd(char *path, t_address add_list);
int			echo(char **args, t_env_var *envp);
int			env(t_env_var *envp, char **args);
void		ft_exit(char *cmd, t_main_data *data);
int			export_arg(char *arg, t_env_var **envp, int builtchecker);
int			export(char **args, t_env_var **envp);
int			pwd();
int			fd_unset(char **args, t_env_var **envp);

//env_utils
t_env_var	*ft_find_env(t_env_var *env, char *key);
int			ft_env_update(t_env_var *env, char *name, char *path);
t_env_var	*add_new_var(void);
void		add_var_back(t_env_var **head, t_env_var *new);
void		duplicate_env_var(t_main_data *data, char **envp);
void		cleanup(t_main_data *data); //exit
int			ft_add_key_val(t_env_var **head, char *keyvalue); //export
void		ft_delete_node(t_env_var **envp, t_env_var *head, int i); //unset
#endif



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:26:53 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/08 16:08:12 by yulpark          ###   ########.fr       */
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


typedef enum s_exec_error{
	MALLOC_FAIL,
	NO_INPUT,
	INVALID_INPUT,
	FAIL_PATH_RETRIEVAL,
	ENV_ERROR,
	SUCCEED

}	t_exec_error;

int				distribution(t_main_data *data);

//builtins

//int			ft_cd(char *path, t_address add_list);
int				echo(char **args);
int				env(t_env_var *envp, char **args);
void			ft_exit(char **cmd, t_main_data *data);
int				export_arg(char *arg, t_env_var **envp);
int				export(char **args, t_env_var **envp);
int				pwd();
int				ft_unset(char **args, t_env_var **envp);

//export_utils
char			*get_var_name(char *arg);
int				input_checker(char *input);
int				create_new_var(char *arg, t_env_var **envp);
int				ft_add_key_val(t_env_var **head, char *keyvalue);

// cd_utils
t_exec_error	input_counter(char **cmd);
char			*ft_strputjoin(char *src1, char *src2, char c);
char			*update_env_value(char *s1, char *s2);
//env_utils
t_env_var		*ft_find_env(t_env_var *env, char *key);
int				ft_env_update(t_env_var *env, char *name, char *path);
void			ft_delete_node(t_env_var **envp, t_env_var *head, int i); //unset
#endif



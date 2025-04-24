/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:26:53 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/24 13:06:50 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <dirent.h>
# include "minishell.h"
# include "libft.h"
# include "tokenization.h"
# include <sys/stat.h>

typedef enum s_exec_error
{
	SUCCEED,
	MALLOC_FAIL,
	NO_INPUT,
	INVALID_INPUT,
	FAIL_PATH_RETRIEVAL,
	ENV_ERROR,
	ERROR = 1
}	t_exec_error;

//builtins

t_exec_error	cd(char **cmd, t_main_data *data);
t_exec_error	env(t_main_data *data, char **args);
void			ft_exit(char **cmd, t_main_data *data);
int				export_arg(char *arg, t_env_var **envp);
t_exec_error	export(char **args, t_main_data *data);
void			echo(char **args);
t_exec_error	pwd(t_main_data *data);
t_exec_error	ft_unset(char **args, t_env_var **envp);

//cd_utils
int				go_prev(t_env_var **envp, char *tb_old_pwd);
int				go_home(t_env_var **envp, char *oldpwd);
void			change_pwd(t_env_var **envp, char *tb_oldpwd, char *pwd);

//export_utils
char			*get_var_name(char *arg);
int				input_checker(char *input);
int				create_new_var(char *arg, t_env_var **envp);
int				ft_add_key_val(t_env_var **head, char *keyvalue);

//env_utils
t_env_var		*ft_find_env(t_env_var *env, char *key);
int				ft_env_update(t_env_var *env, char *name, \
	char *path);
void			ft_delete_node(t_env_var **envp, t_env_var \
	*head, int i);

// execute
t_exec_error	manage_builtins(t_command *cmd, t_main_data *data, int flag);
void			execution(t_main_data *data, t_command *cmd);
void			cmd_executor(t_main_data *data, t_command *cmd, int *fd);
t_exec_error	execute_pipeline(t_main_data *data, t_command *cmd);
bool			builtinchecker(t_command *cmd);

//executable_path
char			*ft_strputjoin(char *src1, char *src2, char c);
void			free_double(char **arr);
char			*executable_path(t_main_data *data, t_command *cmd);

#endif

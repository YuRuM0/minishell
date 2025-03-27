/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:57:30 by flima             #+#    #+#             */
/*   Updated: 2025/03/27 18:01:00 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

static int	read_heredoc_input(t_main_data *data, char *file_name, char *delimiter)
{
	int		fd;
	int		exit_status;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
		heredoc_reading(data, file_name, delimiter);
	waitpid(child_pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) == EXIT_FAIL)
	{
		free(file_name);
		clean_all_data_exit(data, EXIT_CHILD_FAILURE);
	}
	//handle signal_status
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		unlink(file_name);
		hered_err_exit(data, EXIT_DENIED, file_name);
	}
	unlink(file_name);
	free(file_name);
	return (fd);
}

static t_pars_err	creat_file_name(char **file_name, int nbr_heredoc)
{
	char	*prefix;
	char	*heredoc_name;
	
	prefix = "/tmp/heredoc_";
	heredoc_name = ft_itoa(nbr_heredoc);
	if (heredoc_name == NULL)
		return (ERROR_MEM_ALLOC);
	*file_name = ft_strjoin(prefix, heredoc_name);
	if (file_name == NULL)
	{
		free(heredoc_name);
		return (ERROR_MEM_ALLOC);
	}
	free(heredoc_name);
	return (SUCCESS);
}

static t_pars_err	get_current_heredoc(t_main_data *data, t_token *current, int *nbr_heredoc)
{
	int				fd;
	t_pars_err		status;
	char 			*file_name;

	status = creat_file_name(&file_name, *nbr_heredoc);
	if (status != SUCCESS)
		return (status);
	(*nbr_heredoc)++;
	fd = read_heredoc_input(data, file_name, current->next->value);
	
	return (SUCCESS);
}

t_pars_err	capture_heredocs(t_main_data *data)
{
	int			nbr_of_heredoc;
	t_pars_err	status;
	t_token		*current;
	
	nbr_of_heredoc = 0;
	current = data->tokens;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			status = get_current_heredoc(data, current, &nbr_of_heredoc);
			if (status != SUCCESS)
				return (status);
		}
		current = current->next;
	}
	return (SUCCESS);
}
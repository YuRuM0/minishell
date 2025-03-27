/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:13:08 by flima             #+#    #+#             */
/*   Updated: 2025/03/27 15:37:23 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"


void	hered_err_exit(t_main_data *data, t_exit_code status, char *msg)
{
	if (status == EXIT_FAIL)
	{
		error_msg("child process exit failure\n");
		clean_all_data_exit(data, EXIT_FAIL);
	}
	else if (status == EXIT_DENIED)
	{
		error_msg("permission denied or no such file or directory: ");
		write (STDOUT_FILENO, msg, ft_strlen(msg));
		write (STDOUT_FILENO, "\n", 1);
		free(msg);
		clean_all_data_exit(data, EXIT_FAIL);
	}
}


static t_exit_code readline_heredoc(int fd, char *delim)
{
	char	*input;

	while(true)
	{
		input = readline(">");
		if (input == NULL && errno == ENOMEM)
			return(EXIT_MEM_FAILURE);
		if (input == NULL)
			break ;
		if (!ft_strncmp(input, delim, ft_strlen(delim)))
			break ;
		if (write(fd, input, ft_strlen(input)) == -1)
		{
			free(input);
			return (EXIT_DENIED);
		}
		write(fd, "\n", 1);
		free(input);
	}
	return (EXIT_SUCCESSFULLY);
}

void	heredoc_reading(t_main_data *data, char *file_name, char *delim)
{
	int			fd;
	t_exit_code	status;
	
	rl_clear_history();
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		hered_err_exit(data, EXIT_FAIL, NULL);
	status = readline_heredoc(fd, delim);
	close(fd);
	if (status != EXIT_SUCCESSFULLY)
	{
		if (status == EXIT_MEM_FAILURE)
			hered_err_exit(data, EXIT_FAIL, NULL);
		else
			hered_err_exit(data, EXIT_DENIED, file_name);
	}
	free(file_name);
	clean_all_data_exit(data, EXIT_SUCCESSFULLY);
}

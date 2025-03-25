/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:13:08 by flima             #+#    #+#             */
/*   Updated: 2025/03/25 19:09:46 by flima            ###   ########.fr       */
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
		error_msg("permission denied: ");
		error_msg (msg);
		clean_all_data_exit(data, EXIT_FAIL);
	} //mudar isso pois -1 pode ser um arquivo que nao existe tbm
}


char	*readline_heredoc(void)
{
	char	*pipeline;

	pipeline = readline(">");
	if (pipeline == NULL && errno == ENOMEM)
		error_msg(NULL);
	return (pipeline);
}

void	heredoc_reading(t_main_data *data, char *file_name, char *delim)
{
	int		fd;
	char	*input;
	
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		//handle
	free(file_name);
	rl_clear_history();
	while(true)
	{
		input = readline_heredoc();
		if (input == NULL)
			break ;
		if (ft_strncmp(input, delim, ft_strlen(delim)))
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(delim);
	clean_all_data_exit(data, EXIT_SUCCESSFULLY);
	
}
// separar a funcao, vai da mais de 25  linha s
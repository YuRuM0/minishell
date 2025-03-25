/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:49:35 by filipe            #+#    #+#             */
/*   Updated: 2025/03/25 19:07:11 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "tokenization.h"

// void	hered_err_exit(t_main_data *data, t_exit_code status, char *msg)
// {
// 	if (status == EXIT_FAIL)
// 	{
// 		error_msg("child process exit failure\n");
// 		clean_all_data_exit(data, EXIT_FAIL);
// 	}
// 	else if (status == EXIT_DENIED)
// 	{
// 		error_msg("permission denied: ");
// 		error_msg (msg);
// 		clean_all_data_exit(data, EXIT_FAIL);
// 	}
// }

// // char	*readline_heredoc(t_main_data *data, char *prompt, char *delim)
// // {
// // 	char	*pipeline;

// // 	pipeline = readline(prompt);
// // 	add_history(pipeline);
// // 	if (pipeline == NULL && errno == ENOMEM)
// // 	{
// // 		write(STDOUT_FILENO, "error reading input", 20); // temp
// // 		//error_msg - exit minishel, memory alocation fails
// // 	}
// // 	else if (pipeline == NULL && errno == 0) // dignal ctrl + D
// // 	{
// // 		printf("minishell: warning: here-document at line %d delimited "
// // 			"by end-of-file (wanted `%s')\n", data->tty_line, delim);
// // 		rl_clear_history();
// // 		//set teminal tcgetattr function, learn it
// // 	}
// // 	return (pipeline);
// // }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:49:35 by filipe            #+#    #+#             */
/*   Updated: 2025/03/24 18:28:55 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "tokenization.h"

// char    *ft_strtoken(char *str)
// {
//     int     i;
//     int     start;
//     char    *token;

//     if (!*str)
//         return ("\0");
// i = 0;
// while (str[i] == '\t' || str[i] == '\n' || 
//         str[i] == '\r' || str[i] == ' ')
//         i++;
//     if (!str[i])
//         return (NULL);
//     start = i;
//     while (str[i] != '\t' && str[i] != '\n' && 
//         str[i] != '\r' && str[i] != ' ' && str[i])
//         i++;
//     token = ft_substr(str, start, i - start);
//     return (token);
// }

// char	*readline_heredoc(t_main_data *data, char *prompt, char *delim)
// {
// 	char	*pipeline;

// 	pipeline = readline(prompt);
// 	add_history(pipeline);
// 	if (pipeline == NULL && errno == ENOMEM)
// 	{
// 		write(STDOUT_FILENO, "error reading input", 20); // temp
// 		//error_msg - exit minishel, memory alocation fails
// 	}
// 	else if (pipeline == NULL && errno == 0) // dignal ctrl + D
// 	{
// 		printf("minishell: warning: here-document at line %d delimited "
// 			"by end-of-file (wanted `%s')\n", data->tty_line, delim);
// 		rl_clear_history();
// 		//set teminal tcgetattr function, learn it
// 	}
// 	return (pipeline);
// }
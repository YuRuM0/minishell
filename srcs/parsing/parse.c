/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:29:45 by filipe            #+#    #+#             */
/*   Updated: 2025/03/20 17:29:09 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	parser(t_main_data *data)
{
	t_pars_err	status;

	if (data->pipeline == NULL)
		return ;
	if (*(data->pipeline) == '\0')
		return ;
	status = tokenize_input(data, data->pipeline);
	if (status != SUCCESS)
		return (status_error_tokeniz(data, status));
	status = syntax(data);
	if (status != SUCCESS)
		status_error_syntax(data, status);
	debugging(data);
}

// char	*capture_heredoc(t_main_data *data, char *delim)
// {
// 	char	*content;
// 	char	*line;

// 	content = ft_strdup("");
// 	//check erro NULL
// 	while (true)
// 	{
// 		line = readline_heredoc(data, "> ", delim);
// 		if (line == NULL)
// 		{
// 			free(data->heredoc_content);
// 			break ;
// 		}
// 		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		content = ft_strjoin(content, line);
// 		content = ft_strjoin(content, "\n");
// 		//check error NULL;
// 		free(line);
// 	}
// 	return (content);
// }

// void	get_heredoc_delim(t_main_data *data)
// {
//     char    *heredoc_start;
//     char    *heredoc_delim;
//     char    *tmp;

//     tmp = data->pipeline;
//     heredoc_start = ft_strnstr(tmp, "<<", ft_strlen(tmp)); //simple handler
//     if (heredoc_start == NULL)
//         return ; //free data->pipeline
// 	heredoc_delim = ft_strtoken(heredoc_start + 2);
//     if (*heredoc_delim == '\0')
// 	{
// 		printf("minishell: syntax error near unexpected token `newline'\n");
//     	return ;
// 	}
// 	if (heredoc_delim == NULL)
// 		return ; //error in malloc
// 	data->heredoc_content = capture_heredoc(data, heredoc_delim);
// 	printf("%s\n", data->heredoc_content);
// 	if (*(data->heredoc_content) == '\0')
// 		return ; //free?
// }

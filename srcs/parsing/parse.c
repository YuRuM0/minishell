/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:29:45 by filipe            #+#    #+#             */
/*   Updated: 2025/02/21 22:17:08 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_heredoc(t_main_data *data)
{
    char    *heredoc_start;
    char    *heredoc_delim;
    char    *tmp;

    tmp = data->pipeline;
    heredoc_start = ft_strnstr(tmp, "<<", ft_strlen(tmp));
    if (heredoc_start == NULL)
        return ;
    if (heredoc_start != NULL)
    {
        heredoc_delim = ft_strtoken(heredoc_start + 2);
        if (heredoc_delim == NULL)
            return ; //only return? in case after << is empty like echo <<
        printf("%s\n", heredoc_delim);
    }
}

void    parse(t_main_data *data)
{
    if (data->pipeline == NULL || *(data->pipeline) == '\0')
        return ;
    check_heredoc(data);
}
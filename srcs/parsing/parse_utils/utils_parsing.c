/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipe <filipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:49:35 by filipe            #+#    #+#             */
/*   Updated: 2025/03/27 18:42:10 by filipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

char	*check_delimiter_expansion(char *delimiter)
{
	char	*to_return;

	if (delimiter[0] == '\'')
		to_return = ft_strtrim(delimiter, '\'');
	else (delimiter[0] == '\"')
		to_return = ft_strtrim(delimiter, '\"');
	return (to_return);
}
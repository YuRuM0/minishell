/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_especial_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:22:58 by filipe            #+#    #+#             */
/*   Updated: 2025/04/27 16:43:11 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	get_special_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] == '\\')
		{
			len++;
			i += 2;
			continue ;
		}
		else if (str[i] == '\\')
		{
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

static char	*ft_strcpy_without_slash(char *dest, char *src)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (src[++i])
	{
		if (src[i] == '\\' && src[i + 1] && src[i + 1] == '\\')
		{
			dest[j] = src[i];
			i++;
			j++;
		}
		else if (src[i] == '\\')
			continue ;
		else
		{
			dest[j] = src[i];
			j++;
		}
	}
	free(src);
	return (dest);
}

t_pars_err	handle_special_chars(t_token *token)
{
	int		i;
	char	*new_value;

	i = get_special_len(token->value);
	new_value = ft_calloc(i + 1, sizeof(char));
	if (new_value == NULL)
		return (ERROR_MEM_ALLOC);
	token->value = ft_strcpy_without_slash(new_value, token->value);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:38 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/09 17:19:22 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "execution.h"

t_exec_error	input_counter(char **cmd)
{
	if (cmd[2] != NULL)
	{
		error_msg("minishell: cd: too many arguments");
		return (INVALID_INPUT);
	}
	return (SUCCEED);
}

// builds the string
char *update_env_value(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *key = NULL;
	char *value = NULL;
	char *new_str = NULL;

	while (s1[i] && s1[i] != '=')
		i++;
	while (s2[j] && s2[j] != '=')
		j++;
	key = ft_substr(s1, 0, i + 1);  // include =
	if (!key)
		return (NULL);
	value = ft_strdup(&s2[j + 1]); // skip =
	if (!value)
		return (free(key), NULL);
	new_str = ft_strjoin(key, value);
	free(key);
	free(value);
	free(s1);
	return (new_str);
}

char	*ft_strputjoin(char *src1, char *src2, char c)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = ft_strlen(src1);
	j = ft_strlen(src2);
	if (!src1 || !src2)
		return (NULL);
	dst = malloc(i + j + 2);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src1, i + 1);
	dst[i] = c;
	ft_strlcpy(dst + i + 1, src2, j + 1);
	return (dst);
}
*/

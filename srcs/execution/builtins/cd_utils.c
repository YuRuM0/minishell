/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:38 by yulpark           #+#    #+#             */
/*   Updated: 2025/04/08 16:27:38 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//t_exec_error	input_counter(char **cmd)
//{
//	if (cmd[2] != NULL)
//	{
//		error_msg("minishell: cd: too many arguments");
//		return (INVALID_INPUT);
//	}
//	return (SUCCEED);
//}

//char	*update_env_value(char *s1, char *s2)
//{
//	int		i;
//	int		j;
//	char	*key;
//	char	*value;

//	i = 0;
//	j = 0;
//	while (s1[i] != '=')
//		i++;
//	while (s2[j] != '=')
//		j++;
//	ft_strlcpy(key, s1, i + 1);
//	value = ft_strdup(&s2[j]);
//	if (!value)
//		return (NULL);
//	free(s1);
//	s1 = ft_strjoin(key, value);
//	if (!s1)
//		return (NULL);
//	free(key);
//	free(value);
//	return (s1);
//}

//char	*ft_strputjoin(char *src1, char *src2, char c)
//{
//	int		i;
//	int		j;
//	char	*dst;

//	i = 0;
//	j = 0;
//	dst = malloc(ft_strlen(src1) + ft_strlen(src2) + 2);
//    if (!dst)
//         return NULL;
//	if (!src1 || !src2)
//		return (0);
//	while (src1 && src1[i])
//	{
//		dst[j] = src1[i];
//		i++;
//		j++;
//	}
//	dst[j] = c;
//	j++;
//	i = 0;
//	while (src2 && src2[i])
//	{
//		dst[j] = src2[i];
//		j++;
//		i++;
//	}
//	dst[j] = '\0';
//	return (dst);
//}

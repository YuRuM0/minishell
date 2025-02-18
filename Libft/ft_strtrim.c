/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:30:34 by flima             #+#    #+#             */
/*   Updated: 2024/10/14 14:58:24 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
// int	main()
// {
// 	char	str[] = "2Codam nightss2";
// 	char	set[] = "12";
// 	char	*strnew;
// 	size_t	i;

// 	strnew = ft_strtrim(str, set);
// 	printf("%s\n%s\n", strnew, str);
// 	i = ft_strlen(strnew);
// 	printf("%zu", i);
// 	free(strnew);
// 	return (0);

// }
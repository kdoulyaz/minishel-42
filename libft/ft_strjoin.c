/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:00:43 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/07 02:14:24 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

// static char	*rest(char const *s1, char const *s2, char *dest)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	if (dest)
// 	{
// 		j = 0;
// 		while (s1[j])
// 		{
// 			dest[i] = s1[j];
// 			i++;
// 			j++;
// 		}
// 		j = 0;
// 		while (s2[j])
// 		{
// 			dest[i] = s2[j];
// 			i++;
// 			j++;
// 		}
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_strjoin(char	*s1, char	*s2)
// {
// 	char	*dest;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!dest)
// 		return (NULL);
// 	if (dest)
// 		dest = rest(s1, s2, dest);
// 	free(s1);
// 	// free((char *)s2);
// 	return (dest);
// }

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}
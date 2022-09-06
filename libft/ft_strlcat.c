/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:19:05 by omeslall          #+#    #+#             */
/*   Updated: 2021/11/10 20:19:15 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	ldest;
	size_t	lsrc;

	i = 0;
	ldest = ft_strlen(dest);
	lsrc = ft_strlen(src);
	if (n <= ldest)
		return (lsrc + n);
	while (i + ldest < n - 1 && src[i] != '\0')
	{
		dest[ldest + i] = src[i];
		i++;
	}
	dest[ldest + i] = '\0';
	return (lsrc + ldest);
}

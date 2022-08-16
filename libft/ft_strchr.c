/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:46:32 by omeslall          #+#    #+#             */
/*   Updated: 2021/11/10 19:46:49 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*s;
	int		len;

	s = (char *)str;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (*s++ == (char)c)
			return (s - 1);
	}
	return (NULL);
}

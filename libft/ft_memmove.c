/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:41:48 by omeslall          #+#    #+#             */
/*   Updated: 2021/11/14 18:55:33 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*cdst;
	const char		*csrc;
	char			*revdst;
	const char		*revsrc;

	cdst = dst;
	csrc = src;
	revdst = cdst + (len - 1);
	revsrc = csrc + (len - 1);
	if (dst == src || len == 0)
		return (dst);
	if (dst < src)
		while (len--)
			*cdst++ = *csrc++;
	else
		while (len--)
			*revdst-- = *revsrc--;
	return (dst);
}

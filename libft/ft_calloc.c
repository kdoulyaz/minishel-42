/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:07:47 by omeslall          #+#    #+#             */
/*   Updated: 2021/11/14 18:58:05 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*str;

	i = count * size;
	str = malloc(i);
	if (!str)
		return (NULL);
	return (ft_bzero(str, i));
}

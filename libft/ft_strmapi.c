/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:52:04 by omeslall          #+#    #+#             */
/*   Updated: 2021/11/11 15:34:26 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	sub = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[i])
	{
		sub[i] = (*f)(i, s[i]);
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

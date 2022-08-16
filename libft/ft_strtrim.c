/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:56:22 by omeslall          #+#    #+#             */
/*   Updated: 2021/11/16 15:47:11 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	beg(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			if (set[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

static int	end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			if (set[j + 1] == '\0')
				return (i);
			j++;
		}
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	if (!s1)
		return (NULL);
	if (set[0] == '\0')
	{
		str = ft_substr(s1, 0, ft_strlen(s1));
		return (str);
	}
	i = beg(s1, set);
	j = end(s1, set);
	k = j - i + 1;
	if (k < 0)
		k = 0;
	str = ft_substr(s1, i, k);
	return (str);
}

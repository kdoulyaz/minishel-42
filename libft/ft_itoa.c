/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:44:22 by omeslall          #+#    #+#             */
/*   Updated: 2021/11/16 14:55:30 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numbers(long n)
{
	long	m;
	int		count;

	count = 0;
	m = n;
	if (n == 0)
		count = 1;
	while (m > 0)
	{
		m = m / 10;
		count++;
	}
	return (count);
}

static void	ft_iter(char *str, int count, long j, long m)
{
	if (count == 1)
		str[--count] = j + 48;
	else
	{
		while (count--)
		{
			m = j % 10;
			j = j / 10;
			str[count] = m + 48;
		}
	}
}

char	*ft_itoa(int n)
{
	int		count;
	long	m;
	char	*str;
	int		negative;
	long	j;

	j = n;
	m = 0;
	count = j < 0;
	negative = j < 0;
	if (j < 0)
		j = j * -1;
	count = count + count_numbers(j);
	str = (char *)malloc(count * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str [count] = '\0';
	ft_iter(str, count, j, m);
	if (negative == 1)
		str [0] = '-';
	return (str);
}

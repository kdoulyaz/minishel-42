/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qaout_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:27:42 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/25 01:38:22 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	position_quote_s(char *s, int f)
{
	static int	i;

	while (s[i])
	{
		if (s[i] == '\'')
			return (i++);
		i++;
	}
	if (f == 1)
		i = 0;
	return (i);
}

int	utils3_position_quote(int j, int *i, int *q, char *tmp)
{
	*tmp = '\'';
	*q += 1;
	*i += 1;
	j = *i - 1;
	return (j);
}

void	utils1_position_quote(int f, int *i, int *q, char *tmp)
{
	if (f == 1)
	{
		*i = 0;
		*q = 0;
		*tmp = '\0';
	}
}

int	utils2_position_quote(int j, int *i, int *q, char *tmp)
{
	*tmp = '"';
	*q += 1;
	*i += 1;
	j = *i - 1;
	return (j);
}

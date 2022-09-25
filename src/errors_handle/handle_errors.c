/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:26:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/25 02:59:58 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	ft_cmp(char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	handle_quotes(char *s)
{	
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == 39)
		{
			if (ft_cmp(s, s[i]) == 2)
				break ;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

char	quotes_exist(char *argv, size_t *i)
{
	while (argv[*i])
	{
		if (argv[*i] == '"' || argv[*i] == 39)
			return (argv[*i]);
		*i += 1;
	}
	return (0);
}

int	ft_skip_whitespace(char *av, int *i)
{
	while (av[*i] == ' ' || av[*i] == '\t')
		*i += 1;
	return (0);
}

int	red_error(int *i, int *j, char *argv)
{
	int		error;
	char	c1;
	char	c2;

	error = 0;
	c1 = '>';
	c2 = '<';
	while (argv[*i] == c1 || argv[*i] == c2)
	{
		*i += 1;
		*j += 1;
		ft_skip_whitespace(argv, i);
		if (!ft_isalnum(argv[*i]) \
		|| (argv[*i] == c1 && argv[(*i) - 1] == c2) \
		|| (argv[*i] == c2 && argv[(*i) - 1] == c1) \
		|| ((argv[*i] == c1 || argv[*i] == c2) \
		&& (argv[(*i) + 1] == argv[(*i) + 2])))
			error = 1;
	}
	return (error);
}

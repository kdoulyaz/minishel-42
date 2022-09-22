/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:12:27 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/21 23:17:12 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	handle_redirections(char *argv, size_t *j)
{
	int	count;
	int	i;

	count = 0;
	i = *j;
	while (argv[i])
	{
		if (argv[i] == '>')
		{
			if (red_error(&i, &count, argv) || count > 2)
				return (0);
		}
		count = 0;
		if (argv[i] == '<')
		{
			if (red_error(&i, &count, argv) == 1 || count > 2)
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	quotes(char *argv)
{
	size_t	i;
	char	c;

	i = 0;
	while (argv[i])
	{	
		c = quotes_exist(argv, &i);
		if (c)
		{
			i++;
			while (argv[i] && argv[i] != c)
				i++;
			if (i == ft_strlen(argv))
			{
				write(2, "Error unclosed quotes\n", 23);
				return (0);
			}
		}
		if (i < ft_strlen(argv))
			i++;
	}
	return (1);
}

int	handle_pipe(char *argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i] == '|')
		{
			while (j < i && argv[j] == ' ')
				j++;
			if (j == i)
			{
				printf("parse error near `|' \n");
				return (0);
			}
			j = i + 1;
			while (argv[j] && argv[j] == ' ')
				j++;
			if (j == (int)ft_strlen(argv))
			{
				printf("parse error near `|' \n");
				return (0);
			}
			if (!ft_isalnum(argv[i - 1]) || !ft_isalnum(argv[i + 1]))
			{
				printf("parse error near `|' \n");
				return (0);
			}
			if ((argv[i + 1] == '|' && argv[i - 1] == '|')
				|| argv[i - 1] == '<')
			{
				printf("parse error near `|' \n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	handle_errors(char *argv)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (!quotes(argv))
		return (0);
	while (argv[i])
	{
		if (argv[i] == '"' || argv[i] == 39)
		{
			j = i + 1;
			while (argv[j] != argv[i])
				j++;
			i = j;
		}
		if (!handle_redirections(argv, &i))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (0);
		}
		i++;
	}
	if (!handle_pipe(argv))
		return (0);
	return (1);
}

void	path_err(void)
{
	write(2, "path dosn't exist\n", 18);
	exit(1);
}

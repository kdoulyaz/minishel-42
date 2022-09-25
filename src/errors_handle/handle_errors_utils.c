/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:10:19 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/25 03:10:17 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	utils_handle_pipe(char *argv, int *i, int *j)
{
	if (*j == (int)ft_strlen(argv))
	{
		printf("parse error near `|' \n");
		return (0);
	}
	if (!ft_isalnum(argv[(*i) - 1]) || !ft_isalnum(argv[(*i) + 1]))
	{
		printf("parse error near `|' \n");
		return (0);
	}
	if ((argv[(*i) + 1] == '|' && argv[(*i) - 1] == '|' )
		|| argv[(*i) - 1] == '<')
	{
		printf("parse error near `|' \n");
		return (0);
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
			ft_skip_whitespace(argv, &j);
			if (j == i)
			{
				printf("parse error near `|' \n");
				return (0);
			}
			j = i + 1;
			ft_skip_whitespace(argv, &j);
			if (!utils_handle_pipe(argv, &i, &j))
				return (0);
		}
		i++;
	}
	return (1);
}

int	handle_redirections(char *argv, size_t *j)
{
	int	count;
	int	i;

	count = 0;
	i = *j ;
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

int	handle_errors(char *argv)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!quotes(argv))
		return (0);
	while (argv[i])
	{
		utils_handle_errors(argv, &i, &j);
		if (!handle_redirections(argv, &i) \
		&& (argv[i] == '>' || argv[i] == '<'))
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

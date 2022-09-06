/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:26:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/13 18:54:18 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	ft_cmp(char *s, char c)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while(s[i])
	{
		if(s[i] == c)
			count++;
		i++; 
	}
	return(count);
}

int	handle_quotes(char *s)
{	
	int i;

	i = 0;
	while(s[i])
	{
		if(s[i] == '"' || s[i] == 39)
		{
			if(ft_cmp(s, s[i]) == 2)
				break;
			else
				return(0);
		}
		i++;
	}
	return(1);
}

char	quotes_exist(char *argv, size_t *i)
{
	while(argv[*i])
	{
		if(argv[*i] == '"' || argv[*i] == 39)
			return(argv[*i]);
		*i += 1;
	}
	return(0);
}

int ft_sperror(char *av, int *i)
{
	while (av[*i])
	{
		if(av[*i] != ' ')
			return(1);
		*i += 1;
	}
	return(0);
}

int red_error(int *i, int *j, char *argv)
{
	int error;

	error = 0;
	char c1 = '>';
	char c2 = '<';
	while(argv[*i] == c1 || argv[*i] == c2)
	{
		*i += 1;
		*j += 1;
		if((argv[*i] == c1 && argv[*i - 1] == c2) ||
			(argv[*i] == c2 && argv[*i - 1] == c1)||
			(!ft_sperror(argv ,i)))
		 	error = 1;
	}
	if(!ft_isalnum(argv[*i]))
		error = 1;
	return(error);
	
}

int handle_redirections(char *argv, size_t *j)
{
	int count;

	count = 0;
	int i = *j ;
	while(argv[i])
	{
		if(argv[i] == '>')
		{
			if(red_error(&i, &count, argv) || count > 2)
				return(0);
		}
		count = 0;
		if(argv[i] == '<')
		{
			if(red_error(&i, &count, argv) == 1 || count > 2)
				return(0);
		}
		else
			i++;
	}
	return(1);
}

int	quotes(char *argv)
{
	size_t i;

	i = 0;
	while(argv[i])
	{	
		char c = quotes_exist(argv, &i);
		if(c)
		{
			i++;
			while(argv[i] && argv[i] != c)
				i++;
			if( i == ft_strlen(argv))
			{
				write(2, "Error unclosed quotes\n", 23);
				return(0);
			}
		}
        if(i < ft_strlen(argv))
            i++;
	}
	return(1);
}

int	handle_pipe(char *argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(argv[i])
	{
		if(argv[i] == '|')
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
				return(0);
			}
			if((argv[i + 1] == '|' &&  argv[i - 1] == '|' )
				|| argv[i - 1] == '<')
			{
				printf("parse error near `|' \n");
				return(0);
			}
		}
		i++;
	}
	return(1);
}

int	handle_errors(char *argv)
{
	size_t i;
	int j;

	i = 0;
	j = 0;
	if(!quotes(argv))
		return(0);
	while(argv[i])
	{
		if(argv[i] == '"' || argv[i] == 39)
		{
			j = i + 1;
			while(argv[j] != argv[i])
				j++;
			i = j;
		}
		if (!handle_redirections(argv, &i))
		{
			printf("syntax error near unexpected token `newline'\n");
			return(0);
		}
		i++;
	}
	if(!handle_pipe(argv))
		return(0);
	return(1);
} 
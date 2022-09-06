/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qaout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:59:02 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/06 02:07:32 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	position_quote_s(char *s, int f)
{
	static int i;

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

void	single_quote(char *value,char **arg,int i)
{
	char	*tmp;
	int		j;
	
	j = 0;
	j = position_quote_s(value,0);
	if((int)ft_strlen(value) < i)
		{
			position_quote_s(value,1);
			return;
		}
	tmp = ft_substr(value,i,j);
	*arg = ft_strjoin(*arg,tmp);
	free(tmp);
	single_quote(value,arg,j + 1);
}

int	position_quote_d(char *s,int f)
{
	static int i;

	while (s[i])
	{
		if (s[i] == '"')
			return (i++);
		i++;
	}
	if (f == 1)
		i = 0;
	return (i);
}

void	double_quote(t_list *exec,char *value,char **arg,int i)
{
	char	*tmp;
	int		j;
	int   	q;
	
	j = 0;
	q = 0; 
	j = position_quote_d(value,0);
	if((int)ft_strlen(value) < i)
		{
			position_quote_d(value,1);
			return;
		}
	tmp = ft_substr(value,i,j);
	if(check_if_expand(tmp))
	{
		expand(tmp,&tmp);
		// if(check_qaout(tmp) == 1)
		// {
		// }
		// else
		// 	expand(exec,tmp,&tmp);
	}
	*arg = ft_strjoin(*arg,tmp);
	free(tmp);
	double_quote(exec,value,arg,j + 1);
}

void	qaout(t_list *exec, char *value, char **arg, int i)
{
	int		j;
	char	*tmp;
	j = 0;
	if((int)ft_strlen(value) <= i)
	{
		position_quote(value,1);
		return;
	}
	j = position_quote(value,0);
	tmp	= ft_substr(value,i,j + 1);
	if(check_qaout(tmp) == 1)
		single_quote(tmp,arg,0);
	else if(check_qaout(tmp) == 2)
		double_quote(exec,tmp,arg,0);
	else if(check_if_expand(tmp))
	{
		tmp = ft_strjoin(*arg,tmp);
		expand(tmp,arg);
		expand_split(exec,*arg,0);
		free(*arg);
		*arg = ft_strdup("");
		// free(*arg);
		// *arg = ft_strdup("");
	}
	else
		*arg = ft_strjoin(*arg,tmp);
	free(tmp);
	qaout(exec,value,arg,j + 1);
}

int	position_quote(char *s, int f)
{
	static int	i;
	static int	q;
	static char	tmp;
	int			j;


	while (s[i])
	{
		if (s[i] == '"' && q == 0)
		{
			tmp = '"';
			q++;
			j = (i++) - 1;
			return(j);
		}
		else if (s[i] == '\'' && q == 0)
		{
			tmp = '\'';
			q++;
			j = (i++) - 1;
			return(j);
		}
		else if (s[i] == tmp && q == 1)
		{
			tmp = '\0';
			q = 0;
			return (i++);
		}
		i++;
	}
	if (f == 1)
	{
		i = 0;
		q = 0;
		tmp = '\0';
	}
	return (i);
}
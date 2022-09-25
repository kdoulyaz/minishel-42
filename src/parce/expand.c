/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:59:48 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 19:49:12 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
		return (1);
	return (0);
}

int	check_if_expand(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	expand(t_list *exec, char *value, char **arg)
{
	int		i;
	char	*tmp;
	char	*c;
	int		j;

	j = 0;
	tmp = ft_strdup("");
	c = ft_strdup(" ");
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
			expand_exit_status(&tmp, &i);
		else if (value[i] == '$' && is_white_space(value[i + 1]) == 0)
			utils_expand(exec, value, &tmp, &i);
		else
		{
			c[0] = value[i];
			tmp = ft_strjoin(tmp, c);
		}
		i++;
	}
	*arg = ft_strdup(tmp);
	free(c);
	free(tmp);
}

char	*fill_expand(t_list *exec, char *value)
{
	int	i;
	int	len;

	i = -1;
	(void)exec;
	value = ft_strjoin(value, "=");
	while (g_glob.envp[++i])
	{
		if (ft_strncmp(g_glob.envp[i], value, ft_strlen(value)) == 0)
		{
			len = ft_strlen(value);
			free(value);
			value = ft_strdup(g_glob.envp[i] + len);
			return (value);
		}
	}
	free(value);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:00:05 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/31 20:19:51 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_new_line(char *name, char *value)
{
	char	*tmp;

	tmp = ft_calloc(1, sizeof(char));
	tmp = ft_join(tmp, "declare -x ");
	tmp = ft_join(tmp, name);
	if (value)
	{
		tmp = ft_join(tmp, "=\"");
		tmp = ft_join(tmp, value);
		tmp = ft_join(tmp, "\"");
	}
	return (tmp);
}

char	*get_name(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * get_index(str, '=') + 1);
	if (!tmp)
		return (NULL);
	while (++i < get_index(str, '='))
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}

int	is_variable_exist(char *name)
{
	int		i;
	char	*tmp;

	tmp = get_new_line(name, NULL);
	i = -1;
	while (g_glob.exp[++i])
	{
		if (ft_strncmp(g_glob.exp[i], tmp,\
				big_len(get_index(g_glob.exp[i], '='), ft_strlen(tmp))) == 0)
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (-1);
}
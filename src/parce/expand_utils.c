/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:24:17 by omeslall          #+#    #+#             */
/*   Updated: 2022/10/02 20:04:42 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils_expand_split(t_list *exec, char **tmp, int f)
{
	int	i;

	i = -1;
	if (f == 1 && len_2d_array((void *)tmp) != 1)
	{
		((t_data *)exec->content)->error = 1;
		while (tmp[++i])
			free(tmp[i]);
		position_quote(" ", 1);
	}
	else if (f == 1 && len_2d_array((void *)tmp) == 1)
	{
		i = -1;
		while (tmp[++i])
			free(tmp[i]);
	}
}

void	expand_split(t_list *exec, char *arg, int f)
{
	char	**tmp;
	int		i;
	int		len;

	i = -1;
	tmp = ft_split(arg, ' ');
	utils_expand_split(exec, tmp, f);
	while (tmp[++i] && f == 0)
	{
		len = len_2d_array((void **)(((t_data *)exec->content)->args));
		((t_data *)exec->content)->args = (char **)ft_2d_realloc \
		((void **)(((t_data *)exec->content)->args), len + 1);
		((t_data *)exec->content)->args[len] = ft_strdup(tmp[i]);
		free(tmp[i]);
	}
	free(tmp);
}

void	expand_exit_status(char **tmp, int *i)
{
	char	*tmp1;

	tmp1 = ft_itoa(g_glob.g_exit_status);
	if (tmp1)
	{
		*tmp = ft_strjoin(*tmp, tmp1);
		free(tmp1);
	}
	*i += 1;
}

int	next_expand(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '$')
		i++;
	while (s[i])
	{
		if ((s[i] >= 32 && s[i] <= 47) || (s[i] >= 58 && s[i] <= 64)
			|| (s[i] >= 91 && s[i] <= 96) || (s[i] >= 123 && s[i] <= 126))
			return (i);
		i++;
	}
	return (i);
}

void	utils_expand(t_list *exec, char *value, char **tmp, int *i)
{
	int		j;
	char	*tmp1;

	j = 0;
	j = next_expand(&value[*i]) + *i;
	tmp1 = fill_expand(exec, ft_substr(value, *i + 1, j));
	if (tmp1)
	{
		*tmp = ft_strjoin(*tmp, tmp1);
		free (tmp1);
	}
	if (j <= (int)ft_strlen(value))
			*i = j - 1;
}

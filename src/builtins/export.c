/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:17:08 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/24 19:33:53 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_set_export(char *name, char *value, int exist)
{
	int		j;
	char	*tmp;

	j = -1;
	tmp = get_new_line(name, value);
	if (exist)
	{
		while (value && g_glob.exp[++j])
		{
			if (!ft_strncmp(g_glob.exp[j], tmp,
					big_len(g_index(g_glob.exp[j], '='), g_index(tmp, '='))))
			{
				free(g_glob.exp[j]);
				g_glob.exp[j] = ft_strdup(tmp);
				free(tmp);
				return ;
			}
		}
	}
	else
		g_glob.exp = add_env(g_glob.exp, tmp);
	free(tmp);
}

char	*join_tmp(char *tmp, char *name, char *value)
{
	tmp = ft_calloc(1, sizeof(char));
	tmp = ft_join(tmp, name);
	tmp = ft_join(tmp, "=");
	tmp = ft_join(tmp, value);
	return (tmp);
}

void	ft_set_env(char *name, char *value)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	tmp = NULL;
	if (!value)
		return ;
	tmp = join_tmp(tmp, name, value);
	while (g_glob.envp[++i])
	{
		tmp2 = g_v_n(g_glob.envp[i]);
		if (!ft_strncmp(tmp2, name, big_len(ft_strlen(tmp2), ft_strlen(name))))
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strdup(tmp);
			free(tmp);
			free(tmp2);
			return ;
		}
		free(tmp2);
	}
	g_glob.envp = add_env(g_glob.envp, tmp);
	free(tmp);
}

void	new_environment(t_list *exec)
{
	int		i;
	char	**tmp;
	char	*name;
	char	*value;

	i = 0;
	tmp = ((t_data *)exec->content)->args;
	while (tmp[++i])
	{
		value = NULL;
		name = get_name(tmp[i]);
		if ((!name || !name[0]) || check_error(name))
		{
			(error_export(tmp[i]), free(name));
			continue ;
		}
		if (ft_strchr(tmp[i], '='))
			value = ft_strdup(tmp[i] + get_index(tmp[i], '=') + 1);
		if (is_variable_exist(name) != -1)
			(ft_set_env(name, value), ft_set_export(name, value, 1));
		else
			(ft_set_env(name, value), ft_set_export(name, value, 0));
		free(name);
		free(value);
	}
}

int	export_cmd(t_list *exec)
{
	int		len;
	int		i;

	i = -1;
	len = count_args(((t_data *)exec->content)->args);
	if (len == 2)
		while (g_glob.exp[++i])
			printf("%s\n", g_glob.exp[i]);
	else
		new_environment(exec);
	return (0);
}

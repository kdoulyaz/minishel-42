/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:17:08 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/25 17:01:37 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_export(char *name, char *value, int exist)
{
	int		j;
	char	*tmp;

	j = -1;
	tmp = new_line(name, value);
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

void	set_env(char *name, char *value)
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

void	new_env(t_list *exec)
{
	int		i;
	char	**tmp;
	char	*nom;
	char	*val;

	i = 0;
	tmp = ((t_data *)exec->content)->args;
	while (tmp[++i])
	{
		val = NULL;
		nom = get_name(tmp[i]);
		if ((!nom || !nom[0]) || check_error(nom))
		{
			(error_export(tmp[i]), free(nom));
			continue ;
		}
		if (ft_strchr(tmp[i], '='))
			val = ft_strdup(tmp[i] + get_index(tmp[i], '=') + 1);
		if (is_exist(nom) != -1)
			(set_env(nom, val), set_export(nom, val, 1));
		else
			(set_env(nom, val), set_export(nom, val, 0));
		free(nom);
		free(val);
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
		new_env(exec);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:17:08 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/29 22:52:20 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (i);
}

int	big_len(int s1, int s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
}

char	*get_new_line(char *name, char *value)
{
	char	*tmp;

	tmp = ft_calloc(1, sizeof(char));
	tmp = advanced_join(tmp, "declare -x ");
	tmp = advanced_join(tmp, name);
	if (value)
	{
		tmp = advanced_join(tmp, "=\"");
		tmp = advanced_join(tmp, value);
		tmp = advanced_join(tmp, "\"");
	}
	return (tmp);
}

void	ft_set_export(char *name, char *value, int exist, t_list *exec)
{
	int		j;
	char	*tmp;

	(void)exec;
	j = -1;
	tmp = get_new_line(name, value);
	if (exist)
	{
		while (value && g_data.exp[++j])
		{
			if (!ft_strncmp(g_data.exp[j], tmp,
					big_len(get_index(g_data.exp[j], '='), get_index(tmp, '='))))
			{
				free(g_data.exp[j]);
				g_data.exp[j] = ft_strdup(tmp);
				free(tmp);
				return ;
			}
		}
	}
	else
		g_data.exp = add_env(g_data.exp, tmp);
	free(tmp);
}

void	ft_set_env(char *name, char *value, t_list *exec)
{
	int		i;
	char	*tmp;
	char	*tmp2;

    i = -1;
	if (!value)
		return ;
	tmp = ft_calloc(1, sizeof(char));
	tmp = advanced_join(tmp, name);
	tmp = advanced_join(tmp, "=");
	tmp = advanced_join(tmp, value);
	while (((t_data *)exec->content)->envp[++i])
	{
		tmp2 = get_variable_name(((t_data *)exec->content)->envp[i]);
		if (!ft_strncmp(tmp2, name, big_len(ft_strlen(tmp2), ft_strlen(name))))
		{
			free(((t_data *)exec->content)->envp[i]);
			((t_data *)exec->content)->envp[i] = ft_strdup(tmp);
			free(tmp);
			free(tmp2);
			return ;
		}
		free(tmp2);
	}
	((t_data *)exec->content)->envp = add_env(((t_data *)exec->content)->envp, tmp);
	free(tmp);
}

int	is_variable_exist(char *name, t_list *exec)
{
	int		i;
	char	*tmp;

	(void)exec;
	tmp = get_new_line(name, NULL);
	i = -1;
	while (g_data.exp[++i])
	{
		if (ft_strncmp(g_data.exp[i], tmp,
				big_len(get_index(g_data.exp[i], '='), ft_strlen(tmp))) == 0)
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (-1);
}

void	error_export(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	// g_glob.g_exit_status = 1;
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
			value = ft_strdup(tmp[i] + get_char_index(tmp[i], '=') + 1);
		if (is_variable_exist(name, exec) != -1)
			(ft_set_env(name, value, exec), ft_set_export(name, value, 1, exec));
		else
			(ft_set_env(name, value, exec), ft_set_export(name, value, 0, exec));
		free(name);
		free(value);
	}
}

int	export_cmd(t_list *exec)
{
	int		len;
    int     i;

	i = -1;
    len = count_args(((t_data *)exec->content)->args);
	if (len == 2)
        while(g_data.exp[++i])
            printf("%s\n", g_data.exp[i]);
	else
		new_environment(exec);
    return (0);
}

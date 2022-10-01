/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:09:59 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/10/01 16:01:56 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_loop(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

char	**remove_elem(char **env, int n)
{
	int		i;
	int		j;
	char	**new;

	i = -1;
	j = -1;
	new = (char **)malloc(sizeof(char *) * (count_args(env) - 1));
	while (env[++i])
		if (i != n)
			new[++j] = ft_strdup(env[i]);
	new[j + 1] = NULL;
	free_loop(env);
	return (new);
}

void	unset_env(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!ft_strncmp(str, "HOME", 4))
		g_glob.h_flag = 1;
	else if (!ft_strncmp(str, "PWD", 3))
		g_glob.flag = 1;
	else if (!ft_strncmp(str, "env", 3))
		g_glob.env = 1;
	while (g_glob.envp[++i])
	{
		tmp = g_v_n(g_glob.envp[i]);
		if (!ft_strncmp(tmp, str, big_len(ft_strlen(tmp), ft_strlen(str))))
		{
			g_glob.envp = remove_elem(g_glob.envp, i--);
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

void	unset_exp(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_glob.exp[++i])
	{
		tmp = new_line(str, NULL);
		if (!ft_strncmp(g_glob.exp[i], tmp,
				big_len(ft_strlen(tmp), g_index(g_glob.exp[i], '='))))
		{
			g_glob.exp = remove_elem(g_glob.exp, i--);
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

int	unset_cmd(char **args)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = args;
	while (tmp[++i])
	{
		if (!tmp[i] || check_error(tmp[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[1]);
			g_glob.g_exit_status = 1;
			continue ;
		}
		unset_env(tmp[i]);
		unset_exp(tmp[i]);
	}
	return (g_glob.g_exit_status);
}

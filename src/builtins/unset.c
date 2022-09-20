/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:09:59 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/20 00:35:09 by kdoulyaz         ###   ########.fr       */
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


char	**ft_remove_element(char **env, int n)
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

char	*get_variable_name(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * get_char_index(str, '=') + 1);
	if (!tmp)
		return (NULL);
	while (++i < get_char_index(str, '='))
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}

void	unset_env(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_glob.envp[++i])
	{
		tmp = get_variable_name(g_glob.envp[i]);
		if (!ft_strncmp(tmp, str, big_len(ft_strlen(tmp), ft_strlen(str))))
		{
			g_glob.envp = ft_remove_element(g_glob.envp, i--);
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
		tmp = get_new_line(str, NULL);
		if (!ft_strncmp(g_glob.exp[i], tmp, \
		big_len(get_index(g_glob.exp[i], '='), get_index(tmp, '='))))
		{
			g_glob.exp = ft_remove_element(g_glob.exp, i--);
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
			continue ;
		}
		unset_env(tmp[i]);
		unset_exp(tmp[i]);
	}
	
    return (0);
}
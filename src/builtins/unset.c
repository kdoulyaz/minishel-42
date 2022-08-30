/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:09:59 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/29 18:50:20 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	// free_loop(env);
	return (new);
}

int	get_char_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
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

void	unset_env(char *str, t_list *exec)
{
	int		i;
	char	*tmp;

	i = -1;
	while (((t_data *)exec->content)->envp[++i])
	{
		tmp = get_variable_name(((t_data *)exec->content)->envp[i]);
		if (!ft_strncmp(tmp, str, ft_strlen(tmp)))
		{
			((t_data *)exec->content)->envp = ft_remove_element(((t_data *)exec->content)->envp, i--);
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

void	error_unset(char *name)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_glob.g_exit_status = 1;
}

int	is_acceptable(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

int	check_error(char *arg)
{
	int	i;

	if (ft_isdigit(arg[0]))
		return (1);
	i = 1;
	while (arg[i])
	{
		if (!is_acceptable(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	unset_cmd(char **args, t_list *exec)
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
		unset_env(tmp[i], exec);
	}
    free(tmp);
    return (0);
}
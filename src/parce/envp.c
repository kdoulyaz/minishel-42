/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:57:52 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/29 15:58:31 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

char	**add_env(char **strs, char *arg)
{
	char	**args;
	int		i;

	if (!strs[0])
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(arg);
		args[1] = NULL;//free
		return (args);
	}
	args = (char **)malloc(sizeof(char *) * (count_args(strs) + 1));
	i = -1;
	while (strs[++i])
		args[i] = ft_strdup(strs[i]);
	args[i] = ft_strdup(arg);
	args[i + 1] = NULL;//free strs
	return (args);
}

char    **create_envp(char **envp)
{
    char	**env;
	int		i;

	i = -1;
	env = ft_calloc(1, sizeof(char *));
	while(envp[++i])
		env = add_env(env, envp[i]);
	return (env);
}
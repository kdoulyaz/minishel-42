/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 05:14:19 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/16 05:21:46 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_cmd(char **args, t_list *data)
{
	int		chdir_check;
	char	*path;
	char	*tmp;

	if (!args[1] || ((args[1][0] == '~' && ft_strlen(args[1]) == 1)))
		return (set_path(data, "HOME"));
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = check_path(data, args[1]);
	if (!path)
		return (1);
	tmp = getcwd(NULL, 0);
	chdir_check = chdir(path);
	if (chdir_check == 0)
	{
		set_env(data->env, data, "OLDPWD", ft_strdup(tmp, data));
		free(tmp);
		update_env(data->env, data);
		return(0);
	}
	if (chdir_check == -1)
	{
		ft_putstr_fd("minishell: cd: no such  file or directory \n", 2);
		free(tmp);
		return(1);
	}

	// if (args[1][0] == '-' && args[1][1] == '\0')
	// 	return (set_path(data, "OLDPWD"));

	return (0);
}
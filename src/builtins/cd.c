/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 05:14:19 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/22 02:19:38 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env(char *old_pwd, char *new_path)
{
	int	i;

	i = 1;
	new_path = ft_join1(ft_strdup("PWD="), ft_strdup(new_path));
	old_pwd = ft_join1(ft_strdup("OLDPWD="), ft_strdup(old_pwd));
	while (g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "PWD=", 4))
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strdup(new_path);
			break ;
		}
	}
	while (g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "OLDPWD=", 7))
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strdup(old_pwd);
			break ;
		}
	}	
}

int	cd_only(char **args)
{
	if (args[1] == NULL || ((args[1][0] == '~') && ft_strlen(args[1]) == 1))
	{
		if (g_glob.h_flag == 1 && args[1] == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			g_glob.h_flag = 2;
			return (0);
		}
		return (1);
	}
	return (0);
}

int	err_cd(char **args, int flag)
{
	if (flag == 1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 28);
	}
	else
		write(2, "minishell: cd: HOME not set\n", 28);
	return (0);
}

int	cd_cmd(char **args)
{
	char	*new_path;
	char	*old_pwd;

	new_path = getcwd(NULL, 0);
	old_pwd = new_path;
	if (args[1] == NULL || ((args[1][0] == '~') && ft_strlen(args[1]) == 1))
	{
		if (g_glob.h_flag == 1 && args[1] == NULL)
			return (err_cd(args, 0));
		new_path = getenv("HOME");
	}
	else if (args[1][0] == '/')
		new_path = args[1];
	else
	{
		new_path = ft_strjoin(new_path, "/");
		new_path = ft_strjoin(new_path, args[1]);
	}
	if (chdir(new_path) == -1)
		err_cd(args, 1);
	new_path = getcwd(NULL, 0);
	update_env(old_pwd, new_path);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 05:14:19 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/27 19:57:18 by kdoulyaz         ###   ########.fr       */
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
	free(new_path);
	free(old_pwd);
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
	return (1);
}

char	*norm_1(char **args, char *new_path, int mode)
{
	if (mode == 0)
	{
		new_path = ft_getenv("HOME=");
		if (new_path == NULL)
		{
			free(new_path);
			new_path = getenv("HOME");
		}
	}
	else if (mode == 1)
	{
		free(new_path);
		new_path = ft_strdup(args[1]);
	}
	else
	{
		new_path = ft_strjoin(new_path, "/");
		new_path = ft_strjoin(new_path, args[1]);
	}
	return (new_path);
}

int	cd_cmd(char **args)
{
	g_glob.new_path = ft_getenv("PWD=");
	g_glob.old_pwd = ft_strdup(g_glob.new_path);
	if (args[1] == NULL || ((args[1][0] == '~') && ft_strlen(args[1]) == 1))
	{
		if (g_glob.h_flag == 1 && args[1] == NULL)
			return (err_cd(args, 0));
		free(g_glob.new_path);
		g_glob.new_path = norm_1(args, g_glob.new_path, 0);
	}
	else if (args[1][0] == '/')
		g_glob.new_path = norm_1(args, g_glob.new_path, 1);
	else
		g_glob.new_path = norm_1(args, g_glob.new_path, 2);
	if (chdir(g_glob.new_path) == -1)
	{
		if (getcwd(NULL, 0) == NULL)
			return (cd_err(), free(g_glob.new_path), free(g_glob.old_pwd), 0);
		err_cd(args, 1);
	}
	if (g_glob.h_flag == 0)
		free(g_glob.new_path);
	g_glob.new_path = getcwd(NULL, 0);
	update_env(g_glob.old_pwd, g_glob.new_path);
	return (free(g_glob.new_path), free(g_glob.old_pwd), g_glob.g_exit_status);
}

int	cd_cmd1(char **args)
{
	g_glob.new_path = ft_strdup(g_glob.pwd);
	g_glob.old_pwd = ft_strdup(g_glob.new_path);
	if (args[1] == NULL || ((args[1][0] == '~') && ft_strlen(args[1]) == 1))
	{
		if (g_glob.h_flag == 1 && args[1] == NULL)
			return (err_cd(args, 0));
		free(g_glob.new_path);
		g_glob.new_path = norm_1(args, g_glob.new_path, 0);
	}
	else if (args[1][0] == '/')
		g_glob.new_path = norm_1(args, g_glob.new_path, 1);
	else
		g_glob.new_path = norm_1(args, g_glob.new_path, 2);
	if (chdir(g_glob.new_path) == -1)
	{
		if (getcwd(NULL, 0) == NULL)
			return (cd_err(), free(g_glob.new_path), free(g_glob.old_pwd), 0);
		err_cd(args, 1);
	}
	if (g_glob.h_flag == 0)
		free(g_glob.new_path);
	g_glob.new_path = getcwd(NULL, 0);
	update_env1(g_glob.old_pwd);
	g_glob.pwd = ft_strdup(g_glob.new_path);
	return (free(g_glob.new_path), free(g_glob.old_pwd), g_glob.g_exit_status);
}

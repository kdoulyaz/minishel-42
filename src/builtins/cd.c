/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 05:14:19 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/10/04 02:42:55 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd(void)
{
	int	i;

	i = 0;
	while (g_glob.envp[i] != NULL)
	{
		if (ft_strncmp(g_glob.envp[i], "PWD=", 4) == 0)
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strjoin(ft_strdup("PWD="), g_glob.pwd);
			break ;
		}
		i++;
	}
}

void	update_oldpwd(void)
{
	int	i;

	i = 0;
	while (g_glob.envp[i] != NULL)
	{
		if (ft_strncmp(g_glob.envp[i], "OLDPWD=", 7) == 0)
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strjoin(ft_strdup("OLDPWD="), g_glob.pwd);
			free(g_glob.pwd);
			return ;
		}
		i++;
	}
	free(g_glob.pwd);
}

char	*cd_home(char *path, char **args)
{
	path = ft_getenv("HOME=");
	if (path == NULL && args[1] == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		g_glob.g_exit_status = 1;
	}
	else
		path = getenv("HOME");
	return (path);
}

int	cd_cmd(char **args)
{
	char	*path;

	path = NULL;
	g_glob.pwd = getcwd(NULL, 0);
	if (args[1] == NULL || (args[1][0] == '~' && ft_strlen(args[1]) == 1))
		path = cd_home(path, args);
	else
		path = args[1];
	if (path && chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": no such file or directory\n", 29);
		g_glob.g_exit_status = 1;
	}
	update_oldpwd();
	path = getcwd(NULL, 0);
	if (path)
	{
		update_pwd();
		free(path);
	}
	else
		write(2, "err getcwd\n", 11);
	return (g_glob.g_exit_status);
}

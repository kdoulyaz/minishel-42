/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 05:14:19 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/06 22:28:30 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env(char *old_pwd, char *new_path)
{
	int	i;

	i = 1;
	new_path = ft_join(ft_strdup("PWD="), new_path);
	old_pwd = ft_join(ft_strdup("OLDPWD="), old_pwd);
	while(g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "PWD=", 4))
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strdup(new_path);
			break;
		}
	}
	while(g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "OLDPWD=", 7))
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strdup(old_pwd);
			break;
		}
	}	
}

int	cd_cmd(char **args)
{
	char	*new_path;
	char	*old_pwd;
	int		i;

	i = -1;
	new_path = getcwd(NULL,0);
	old_pwd = new_path;
	if (args[1] == NULL || (args[1][0] == '~' && ft_strlen(args[1]) == 1))
	{
		new_path = NULL;
		while(g_glob.envp[++i])
		{
			if (!ft_strncmp(g_glob.envp[i], "HOME=", 5))
			{
				new_path = g_glob.envp[i] + 5;
				break;
			}
		}
		if (!new_path)
		{
			g_glob.g_exit_status = 1;
			printf("minishell: cd: HOME not set\n");
			return (0);
		}
	}
	else if(args[1][0] == '/')
		new_path = args[1];
	else
	{
		new_path = ft_strjoin(new_path,"/");
		new_path = ft_strjoin(new_path,args[1]);
	}
	if (chdir(new_path) == -1 && new_path)
	{
		g_glob.g_exit_status = 1;
		write(2, "minishell: cd: ", 15);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 28);
		return(0);
	}
	else if(chdir(new_path) == -1)
		printf("9ouwedtouha\n");
	new_path = getcwd(NULL,0);
	update_env(old_pwd, new_path);
	return (0);
}

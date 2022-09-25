/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 04:56:15 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/24 05:43:39 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_err(int i)
{
	if (g_glob.envp[i][4] == '\0')
		write(2, "Err path\n", 9);
	else
		printf("{%s}\n", g_glob.envp[i] + 4);
}

void	util(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s == NULL)
	{
		s = ft_getenv("PWD=");
		printf("%s\n", s);
	}
	else
		printf("%s\n", s);
	free(s);
}

int	pwd_cmd(void)
{
	int		i;

	i = -1;
	while (g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "PWD=", 4))
		{
			pwd_err(i);
			break ;
		}
		else
		{
			util();
			break ;
		}
	}
	return (0);
}

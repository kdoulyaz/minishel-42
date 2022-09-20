/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 04:56:15 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/06 16:55:27 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd(void)
{
	int		i;

	i = -1;
	char *s;
	while (g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "PWD=", 4))
		{
			if (g_glob.envp[i][4] == '\0')
				write(2, "Err path\n", 9);
			else
				printf("{%s}\n", g_glob.envp[i] + 4);
			break ;
		}
		else
		{
			s = getcwd(NULL, 0);
			printf("%s\n", s);
			free(s);
			break;
		}
	}
	return (0);
}

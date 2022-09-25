/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:06:01 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/25 05:44:28 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_cmd(void)
{
	int	i;

	i = -1;
	if (g_glob.env == 1)
	{
		write(2, "minishell: env: No such file or directory\n", 42);
		g_glob.g_exit_status = 127;
	}
	else
		while (g_glob.envp[++i])
			printf("%s\n", g_glob.envp[i]);
	return (g_glob.g_exit_status);
}

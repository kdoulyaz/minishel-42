/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:06:01 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/21 19:07:30 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_cmd(t_list *exec)
{
	int	i;

	i = -1;
	if (!g_glob.envp || ((t_data *)exec->content)->args[1])
	{
		write(2, "minishell: env: No such file or directory\n", 42);
		exit(1);
	}
	else
		while (g_glob.envp[++i])
			printf("%s\n", g_glob.envp[i]);
	return (0);
}

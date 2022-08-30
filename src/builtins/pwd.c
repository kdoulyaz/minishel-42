/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 04:56:15 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/28 16:23:21 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd(t_list	*exec)
{
	int		i;

	i = -1;
	while (((t_data *)exec->content)->envp[++i])
	{
		if (!ft_strncmp(((t_data *)exec->content)->envp[i], "PWD=", 4))
		{
			printf("{%s}\n", ((t_data *)exec->content)->envp[i] + 4);
			break ;
		}
	}
	return (0);
}

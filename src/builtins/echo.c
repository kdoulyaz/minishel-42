/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:15:41 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/21 17:53:21 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_opt(char *args)
{
	int	i;

	i = 2;
	if (args && (args[0] == '-' && args[1] == 'n'))
	{
		while (args[i] == 'n')
			i++;
		if (args[i] == '\0')
			return (1);
	}
	return (0);
}

int	echo_cmd(char **args)
{
	int	i;
	int	bool;

	i = 0;
	bool = 0;
	if (!args[1])
    {
		ft_putstr_fd("\n", 1);
        return(0);
    }
	if (check_opt(args[1]) && !args[2])
		return(0);
	while (check_opt(args[++i]))
		bool++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i] && args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!bool)
		ft_putstr_fd("\n", 1);
	return(0);
}
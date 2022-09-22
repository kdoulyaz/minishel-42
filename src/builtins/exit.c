/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:32:24 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/21 19:12:31 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

void	num(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i] != NULL)
	{
		while (args[1][j])
		{
			if (args[1][j] != '0' && !ft_atoi(&args[1][j]))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				g_glob.g_exit_status = 255;
				exit(g_glob.g_exit_status);
			}
			j++;
		}
		i++;
	}
}

int	exit_cmd(char **args)
{
	int	len;

	len = count_args(args);
	if (!args[1])
	{
		printf("exit\n");
		exit(g_glob.g_exit_status);
	}
	num(args);
	write(2, &len, 4);
	if (len > 3)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_glob.g_exit_status = 1;
	}
	else if (len == 3)
	{
		printf("exit\n");
		exit(ft_atoi(args[1]));
	}
	return (0);
}

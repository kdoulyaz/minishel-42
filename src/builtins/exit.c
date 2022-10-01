/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:32:24 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/10/02 00:31:12 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_status;

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

void	is_numeric(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i] != NULL)
	{
		while (args[1][j])
		{
			if ((args[1][0] == '-' || args[1][0] == '+') && args[1][1] == '0'
			&& !ft_atoi(&args[1][1]))
				(printf("exit\n"), exit(0));
			if (args[1][j] != '0' && !ft_atoi(&args[1][j]))
			{
				write(2, "minishell: exit: ", 17);
				write(2, args[1], ft_strlen(args[1]));
				write(2, ": numeric argument required\n", 28);
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
	long long	len;

	len = count_args(args);
	if (!args[1])
		(printf("exit\n"), exit(g_glob.g_exit_status));
	is_numeric(args);
	write(2, &len, 4);
	if (len > 3)
		write(2, "exit\nminishell: exit: too many arguments\n", 41);
	else if (len == 3)
	{
		len = ft_atoi(args[1]);
		if (args[1][0] != '-' && len < 0)
		{
			write(2, "minishell: exit: ", 17);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		else
			(printf("exit\n"), exit(ft_atoi(args[1])));
	}
	return (0);
}

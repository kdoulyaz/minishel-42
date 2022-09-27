/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 01:41:02 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/25 16:32:57 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	handlear(int signal)
{
	(void)signal;
	if (g_glob.signal_heredoc == 0)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		g_glob.stop = 1;
		g_glob.g_exit_status = 1;
		g_glob.last = 1;
		ft_putstr_fd("\n", 1);
		close(0);
		g_glob.signal_heredoc = 0;
		g_glob.stop = 0;
	}
}

void	init_signal(void)
{
	signal(SIGINT, handlear);
	signal(SIGQUIT, SIG_IGN);
}

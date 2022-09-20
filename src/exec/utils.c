/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:15:07 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/17 15:26:18 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	piping(pid_t *p)
{
	pipe(p);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_dup(int fd, int end)
{
	dup2(fd, end);
	close(fd);
}

void	waiting(t_list *lst)
{
	dup2(g_glob.tmpin, 0);
	dup2(g_glob.tmpout, 1);
	close(g_glob.tmpin);
	close(g_glob.tmpout);
	while (lst)
	{
		wait(NULL);
		lst = lst->next;
	}
	init_signal();
}

int	err_inf(t_list *exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (((t_data *)exec->content)->inf)
	{
		write(2, "minishell: ", 11);
		write(2, ((t_data *)exec->content)->inf, \
		ft_strlen(((t_data *)exec->content)->inf));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}

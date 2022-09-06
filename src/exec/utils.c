/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 00:16:18 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/07 00:53:17 by kdoulyaz         ###   ########.fr       */
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

void	waiting(int tmpin, int tmpout, t_list *lst)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	while(lst)
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


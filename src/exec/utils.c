/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:15:07 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/25 05:36:13 by kdoulyaz         ###   ########.fr       */
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

// void	waiting(t_list *lst)
// {
// 	int	statusl
// 	dup2(g_glob.tmpin, 0);
// 	dup2(g_glob.tmpout, 1);
// 	close(g_glob.tmpin);
// 	close(g_glob.tmpout);
// 	while (lst)
// 	{
// 		waitpid(-1, &status, NULL);
// 		lst = lst->next;
// 	}
// 	init_signal();
// }

void	waiting(t_list *lst)
{
	int		status;

	while (lst)
	{
		waitpid(g_glob.pid, &status, 0);
		if (g_glob.pid != -1)
		{
			if (WIFEXITED(status))
				g_glob.g_exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_glob.g_exit_status = 128 + WTERMSIG(status);
		}
		while (wait(NULL) != -1)
			;
		lst = lst->next;
	}
	init_signal();
}

void	initialise(void)
{
	g_glob.copy_fd = -1;
	g_glob.tmpin = dup(0);
	g_glob.tmpout = dup(1);
	g_glob.g_child = 0;
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
		g_glob.g_exit_status = 127;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:49:56 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/07 00:52:39 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	child_p(t_list *exec, int *p, int copy_fd, char **eenv)
{
	int	fdout;

	fdout = -1;
	open_out(exec, &fdout);
	close(p[0]);
	if (bulitin(exec))
	{
		g_glob.g_exit_status = execute_bulitings(exec);
		g_glob.built = 1;
		return ;
	}
	if (exec->next)
		ft_dup(p[1], 1);
	if (fdout != -1)
		ft_dup(fdout, 1);
	if (copy_fd != -1)
		ft_dup(copy_fd, 0);
	if (((t_data *)exec->content)->infiles)
		ft_dup(((t_data *)exec->content)->\
		infiles[((t_data *)exec->content)->n_infiles - 1], 0);
	if (((t_data *)exec->content)->args && \
	execve(find_path(((t_data *)exec->content)->args[0], \
		eenv), ((t_data *)exec->content)->args, eenv) == -1)
		write(2, "hadi makhedamach\n", 18);
}

int	built_parent(t_list *exec)
{
	int		fdout;
	int		tmpin;
	int		tmpout;

	fdout = -1;
	if (bulitin(exec) && !exec->next)
	{
		tmpin = dup(0);
		tmpout = dup(1);
		open_out(exec, &fdout);
		if (fdout != -1)
			ft_dup(fdout, 1);
		g_glob.g_exit_status = execute_bulitings(exec);
		g_glob.built = 1;
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
		return (0);
	}
	return (1);
}

void	start_exec(t_list *exec, char **eenv)
{
	t_list	*lst;
	pid_t	p[2];
	int		tmpin;
	int		tmpout;
	int		copy_fd;

	lst = exec;
	copy_fd = -1;
	tmpin = dup(0);
	tmpout = dup(1);
	if (built_parent(exec) == 0)
		return ;
	while(exec)
	{
		piping(p);
		g_glob.pid = fork();
		if (g_glob.pid == -1)
		{
			write(2, "bash: fork: Resource temporarily unavailable\n", 45);
			break ;
		}
		if (g_glob.pid == 0)
		{
			if (err_inf(exec) == 1)
				exit(1);
			child_p(exec, p, copy_fd, eenv);
		}
		close(p[1]);
		if (copy_fd != -1)
			close(copy_fd);
		copy_fd = p[0];
		exec = exec->next;
	}
	waiting(tmpin, tmpout, lst);
}

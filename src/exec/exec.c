/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:49:56 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/25 17:20:04 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	built_parent(t_list *exec)
{
	int		tmpin;
	int		tmpout;

	g_glob.fdout = 0;
	initialise();
	if (bulitin(exec) && !exec->next)
	{
		tmpin = dup(0);
		tmpout = dup(1);
		if (open_out1(exec, 0) == 1)
			return (0);
		if (g_glob.fdout != -1)
			ft_dup(g_glob.fdout, 1);
		g_glob.g_exit_status = execute_bulitings(exec, 0);
		g_glob.built = 1;
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
		return (0);
	}
	return (1);
}

void	is_derictory(t_list *exec)
{
	struct stat	s;

	if (ft_strchr(((t_data *)exec->content)->args[0], '/') \
		|| !ft_getenv("PATH="))
	{
		if (stat(((t_data *)exec->content)->args[0], &s) == 0)
		{
			if (S_ISDIR(s.st_mode))
			{
				g_glob.g_exit_status = 126;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(((t_data *)exec->content)->args[0], 2);
				ft_putendl_fd(": is a directory", 2);
				exit(g_glob.g_exit_status);
			}
		}
	}
}

void	child_p(t_list *exec, int *p, int copy_fd)
{
	norm(exec, p, copy_fd);
	if (((t_data *)exec->content)->hd)
		ft_dup(g_glob.end[0], 0);
	if (bulitin(exec))
	{
		g_glob.g_child = 1;
		g_glob.g_exit_status = execute_bulitings(exec, 1);
		exit(0);
	}
	else
	{
		if (((t_data *)exec->content)->args)
		{
			is_derictory(exec);
			if (execve(find_path(((t_data *)exec->content)->args[0], \
			g_glob.envp), ((t_data *)exec->content)->args, g_glob.envp) == -1)
			{
				ree(exec);
				exit(g_glob.g_exit_status);
			}
		}
		else
			exit(0);
	}
}

void	start_exec(t_list *exec)
{
	t_list	*lst;
	int		p[2];

	lst = exec;
	if (built_parent(exec) == 0)
		return ;
	while (exec)
	{
		piping(p);
		g_glob.pid = fork();
		if (err_fork() != 0)
			break ;
		if (g_glob.pid == 0)
		{
			if (err_inf(exec) == 1)
				exit(g_glob.g_exit_status);
			child_p(exec, p, g_glob.copy_fd);
		}
		close(p[1]);
		if (g_glob.copy_fd != -1)
			close(g_glob.copy_fd);
		g_glob.copy_fd = p[0];
		exec = exec->next;
	}
	wait_pids(lst);
}

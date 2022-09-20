/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:49:56 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/19 19:46:56 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

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
		if (open_out1(exec, &fdout) == 1)
			return (0);
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

void	*ft_getenv(char *str)
{
	int	i;

	i = 0;
	if (!g_glob.envp)
		return (NULL);
	while (g_glob.envp[i] != NULL)
	{
		if (ft_strncmp(g_glob.envp[i], str, ft_strlen(str)) == 0)
			return (g_glob.envp[i] + ft_strlen(str));
		i++;
	}
	return (NULL);
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
	int	fdout;

	fdout = -1;
	open_out(exec, &fdout);
	close(p[0]);
	if (exec->next)
		ft_dup(p[1], 1);
	if (fdout != -1)
		ft_dup(fdout, 1);
	if (copy_fd != -1)
		ft_dup(copy_fd, 0);
	if (((t_data *)exec->content)->infiles)
		ft_dup(((t_data *)exec->content)->\
		infiles[((t_data *)exec->content)->n_infiles - 1], 0);
	if (((t_data *)exec->content)->hd)
		ft_dup(g_glob.end[0], 0);
	if (child_bulitin(exec))
	{
		g_glob.g_child = 1;
		g_glob.g_exit_status = child_execute_bulitings(exec);
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
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(((t_data *)exec->content)->args[0], 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd(strerror(errno), 2);
				g_glob.g_exit_status = 127;
				exit(g_glob.g_exit_status);
			}
		}
		else
			exit(0);
	}
}

void	initialise(void)
{
	g_glob.copy_fd = -1;
	g_glob.tmpin = dup(0);
	g_glob.tmpout = dup(1);
	g_glob.g_child = 0;
}

int	err_fork(void)
{
	if (g_glob.pid == -1)
	{
		write(2, "bash: fork: Resource temporarily unavailable\n", 45);
		return (1);
	}
	return (0);
}

void	start_exec(t_list *exec)
{
	t_list	*lst;
	int		p[2];

	lst = exec;
	initialise();
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
				exit(1);
			child_p(exec, p, g_glob.copy_fd);
		}
		close(p[1]);
		if (g_glob.copy_fd != -1)
			close(g_glob.copy_fd);
		g_glob.copy_fd = p[0];
		exec = exec->next;
	}
	waiting(lst);
}

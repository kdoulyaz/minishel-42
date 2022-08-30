/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:49:56 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/28 17:31:27 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	ft_dup(int	fd, int	end)
{
	dup2(fd, end);
	close(fd);
}

void	child_p(t_list *exec, int *p, int copy_fd, char **eenv)
{
	int	fdout;

	fdout = -1;
	open_out(exec, &fdout);
	close(p[0]);
	if (exec->next)
		ft_dup(p[1], 1);
	if (fdout != -1)
		ft_dup(fdout, 1);
	if (bulitin(exec))
	{
		g_glob.g_exit_status = execute_bulitings(exec);
		exit(1);
	}
	if (copy_fd != -1)
		ft_dup(copy_fd, 0);
	if(((t_data *)exec->content)->infiles)
		ft_dup(((t_data *)exec->content)->infiles[((t_data *)exec->content)->n_infiles - 1], 0);
	if (((t_data *)exec->content)->args && execve(find_path(((t_data *)exec->content)->args[0],\
		eenv),((t_data *)exec->content)->args, eenv) == -1)
		write(2, "sir t9ouwed\n", 12);
}
void	start_exec(t_list *exec, char **eenv)
{
	t_list	*lst;
	pid_t	p[2];
	int		tmpin;
	int		tmpout;
	int		pid;
	int		copy_fd;

	lst = exec;
	copy_fd = -1;
	tmpin = dup(0);
	tmpout = dup(1);
	while(exec)
	{
		pipe(p);
		pid = fork();
		if (pid == -1)
		{
			write(2, "bash: fork: Resource temporarily unavailable\n", 45);
			break ;
		}
		if (pid == 0)
		{
			if(((t_data *)exec->content)->inf)
			{
				write(2, "minishell: ", 11);
				write(2, ((t_data *)exec->content)->inf, ft_strlen(((t_data *)exec->content)->inf));
				write(2, ": No such file or directory\n", 28);
				exit(1);
			}
			child_p(exec, p, copy_fd, eenv);
		}
		close(p[1]);
		if (copy_fd != -1)
			close(copy_fd);
		copy_fd = p[0];
		exec = exec->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	while(lst)
	{
		wait(NULL);
		lst = lst->next;
	}
}

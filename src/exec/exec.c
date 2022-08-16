/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:49:56 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/16 03:20:42 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	cmd_err(char *cmd)
{
	write(STDERR_FILENO, "minishell: error: command not found: ", 37);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	path_err(void)
{
	write(2, "path dosn't exist\n", 18);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		path_err();
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		if (ft_strchr(cmd, '/'))
			return (cmd);
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	cmd_err(cmd);
	return (NULL);
}

void	child_p(t_list *lst)
{
	if (((t_data *)lst->content)->inf)
		printf("minishell: %s : No such file or directory\n", ((t_data *)lst->content)->inf);
	if (execve(find_path(((t_data *)lst->content)->args[0], ((t_data *)lst->content)->env),\
		((t_data *)lst->content)->args, ((t_data *)lst->content)->env) == -1)
		printf("ydek 3llo\n");
}
int	redir_input(t_list *lst, int tmpin)
{
	int	fdin;

	if(((t_data *)lst->content)->infiles)
		fdin = ((t_data *)lst->content)->infiles[((t_data *)lst->content)->n_infiles - 1];
	else
		fdin = dup(tmpin);
	return(fdin);
}

void	start_exec(t_list *exec)
{
	t_list	*lst;
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		i;

	lst = exec;
	tmpin = dup(0);
	tmpout = dup(1);
	fdin = redir_input(lst, tmpin);
	while(lst)
	{
		i = 0;
		dup2(fdin, 0);
		close(fdin);
		if (lst->next)
		{
			int	fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		if (((t_data *)lst->content)->outfiles || ((t_data *)lst->content)->append)
		{
			if (((t_data *)lst->content)->outfiles)
			{
				while(((t_data *)lst->content)->outfiles[i])
					fdout = open(((t_data *)lst->content)->outfiles[i++], O_WRONLY | O_CREAT |O_TRUNC ,0777);
				dup2(fdout, 1);
				close(fdout);
			}
			else
			{
				while(((t_data *)lst->content)->append[i])
					fdout = open(((t_data *)lst->content)->append[i++], O_WRONLY | O_CREAT |O_APPEND ,0777);
				dup2(fdout, 1);
				close(fdout);
			}
		}
		else
			fdout = dup(tmpout);
		dup2(fdout, 1);
		close(fdout);
		i = fork();
		if (i == 0)
		{
	close(fdin);
			child_p(lst);
		}
		else
		{
			close(fdout);
		}
		lst = lst->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(-1, NULL, 0);
}

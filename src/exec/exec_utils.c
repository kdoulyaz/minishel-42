/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 06:35:04 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/06 18:52:42 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	cmd_err(char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(1);
}

void	path_err(void)
{
	write(2, "path dosn't exist\n", 18);
	exit(1);
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
	if (!env)
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

void	error_msg(char *str, int err)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
}

void	open_out(t_list *exec, int *fdout)
{
	int	i;

	i = 0;
	if (((t_data *)exec->content)->outfiles || ((t_data *)exec->content)->append)
		{
			if (((t_data *)exec->content)->outfiles)
			{
				while(((t_data *)exec->content)->outfiles[i])
					*fdout = open(((t_data *)exec->content)->outfiles[i++], O_WRONLY | O_CREAT |O_TRUNC ,0777);
				dup2(*fdout, 1);
				close(*fdout);
			}
			else
			{
				while(((t_data *)exec->content)->append[i])
					*fdout = open(((t_data *)exec->content)->append[i++], O_WRONLY | O_CREAT |O_APPEND ,0777);
				dup2(*fdout, 1);
				close(*fdout);
			}
			if (*fdout == -1)
			{
				error_msg(((t_data *)exec->content)->outfiles[--i], errno);
				exit(1);
			}
		}
		// if (((t_data *)exec->content)->error == 1)
		// 	exit(1);
}

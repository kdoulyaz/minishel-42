/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 06:35:04 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/24 20:45:05 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	cmd_err(char *cmd)
{
	g_glob.g_exit_status = 127;
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": Command not found\n", 20);
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
	if (env[i] == NULL)
		path_err();
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		if (ft_strchr(cmd, '/'))
			return (cmd);
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	cmd_err(cmd);
	exit(g_glob.g_exit_status);
}

int	err_out(t_list *exec, int mode, int mode1, int i)
{
	if (mode == 0)
	{
		if (g_glob.fdout == -1)
		{
			if (((t_data *)exec->content)->outfiles && g_glob.j == 0)
				error_msg(((t_data *)exec->content)->outfiles[i], errno);
			else if (((t_data *)exec->content)->append)
				error_msg(((t_data *)exec->content)->append[i], errno);
			if (mode1 == 0)
				exit(1);
			else
				return (1);
		}
	}
	else
	{
		if (((t_data *)exec->content)->error == 1)
		{
			if (mode1 == 0)
				exit(1);
			else
				return (1);
		}
	}
	return (0);
}

void	open_out(t_list *exec, int i)
{
	if (((t_data *)exec->content)->outfiles
		|| ((t_data *)exec->content)->append)
	{
		if (((t_data *)exec->content)->outfiles)
		{
			g_glob.j = 0;
			while (((t_data *)exec->content)->outfiles[i])
				g_glob.fdout = open(((t_data *)exec->content)->outfiles[i++],
						O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(g_glob.fdout, 1);
			close(g_glob.fdout);
		}
		if (((t_data *)exec->content)->append)
		{
			i = 0;
			g_glob.j = 1;
			while (((t_data *)exec->content)->append[i])
				g_glob.fdout = open(((t_data *)exec->content)->append[i++],
						O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2(g_glob.fdout, 1);
			close(g_glob.fdout);
		}
		err_out(exec, 0, 0, i - 1);
	}
	err_out(exec, 1, 0, i - 1);
}

int	open_out1(t_list *exec, int i)
{
	if (((t_data *)exec->content)->outfiles)
	{
		while (((t_data *)exec->content)->outfiles[i])
			g_glob.fdout = open(((t_data *)exec->content)->outfiles[i++],
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(g_glob.fdout, 1);
		close(g_glob.fdout);
	}
	if (((t_data *)exec->content)->append)
	{
		i = 0;
		while (((t_data *)exec->content)->append[i])
			g_glob.fdout = open(((t_data *)exec->content)->append[i++],
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		dup2(g_glob.fdout, 1);
		close(g_glob.fdout);
	}
	if (err_out(exec, 0, 1, i - 1) == 1)
		return (1);
	if (err_out(exec, 1, 1, i - 1) == 1)
		return (1);
	return (0);
}

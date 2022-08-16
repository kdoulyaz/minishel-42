/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 03:14:20 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/16 05:22:25 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	bulitin(t_list *exec)
{
	if (!((t_data *)exec->content)->args[0])
		return (0);
	if (!ft_strncmp(((t_data *)exec->content)->args[0], "cd", 3))
		return (1);
	if (!ft_strncmp(((t_data *)exec->content)->args[0], "pwd", 4))
		return (1);
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "echo", 5))
	// 	return (1);
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "env", 4))
	// 	return (1);
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "export", 7))
	// 	return (1);
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "unset", 6))
	// 	return (1);
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "exit", 6))
	// 	return (1);
	return (0);
}

int	execute_bulitings(t_list *exec)
{
	if (!ft_strncmp(((t_data *)exec->content)->args[0], "cd", 3))
		return (cd_cmd(((t_data *)exec->content)->args), exec);
	if (!ft_strncmp(((t_data *)exec->content)->args[0], "pwd", 4))
		return (pwd_cmd());
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "echo", 5))
	// 	return (echo_cmd(((t_data *)exec->content)->args));
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "env", 4))
	// 	return (env_cmd(exec));
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "export", 7))
	// 	return (export_cmd(((t_data *)exec->content)->args, exec));
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "unset", 6))
	// 	return (unset_cmd(((t_data *)exec->content)->args, exec));
	// else if (!ft_strncmp(((t_data *)exec->content)->args[0], "exit", 6))
	// 	return (exit_cmd(((t_data *)exec->content)->args, exec));
	return (0);
}
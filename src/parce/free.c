/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 03:39:53 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/25 01:34:15 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_exec(t_list *exec)
{
	t_list	*tmp;

	while (exec)
	{
		free_2d_array(((t_data *)exec->content)->args);
		free_2d_array(((t_data *)exec->content)->outfiles);
		free_2d_array(((t_data *)exec->content)->append);
		free_2d_array(((t_data *)exec->content)->hd);
		if (((t_data *)exec->content)->infiles)
		{
			free(((t_data *)exec->content)->infiles);
		}
		if (((t_data *)exec->content)->inf)
		{
			free(((t_data *)exec->content)->inf);
		}
		free(exec->content);
		tmp = exec;
		exec = exec->next;
		free(tmp);
	}
}

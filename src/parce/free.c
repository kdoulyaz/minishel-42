/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 03:39:53 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/15 16:54:15 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void free_exec(t_list* exec)
{
	int i;
	t_list *tmp;
	i = 0;
	while (exec)
	{	
		if(((t_data *)exec->content)->args)
		{
			i = 0;
			while(((t_data *)exec->content)->args[i])
			{
				free(((t_data *)exec->content)->args[i]);
				i++;
			}
			free(((t_data *)exec->content)->args);
		}
		if(((t_data *)exec->content)->infiles)
		{
			free(((t_data *)exec->content)->infiles);
		}
		i = 0;
		if(((t_data *)exec->content)->outfiles)
		{
			while(((t_data *)exec->content)->outfiles[i])
			{
				free(((t_data *)exec->content)->outfiles[i]);
				i++;
			}
			free(((t_data *)exec->content)->outfiles);
		}
		i = 0;
		if(((t_data *)exec->content)->append)
		{
			while(((t_data *)exec->content)->append[i])
			{
				free(((t_data *)exec->content)->append[i]);
				i++;
			}
			free(((t_data *)exec->content)->append);
		}
		i = 0;
		if(((t_data *)exec->content)->hd)
		{
			while(((t_data *)exec->content)->hd[i])
			{
				free(((t_data *)exec->content)->hd[i]);
				i++;
			}
			free(((t_data *)exec->content)->hd);
		}
		if(((t_data *)exec->content)->inf)
		{
			free(((t_data *)exec->content)->inf);
		}
		free(exec->content);
		tmp = exec;
		exec = exec->next;
		free(tmp);
	}
}
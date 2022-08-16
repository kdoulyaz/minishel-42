/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:05:12 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/13 18:56:17 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	fill_pipe(t_list *exec)
{
	t_list *new;
	
	new  =  init_execution();
	ft_lstadd_back(&exec, new);
}
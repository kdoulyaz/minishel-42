/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:24:17 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/07 02:39:22 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	expand_split(t_list *exec,char *arg,int f)
{
	char **tmp;

	int	i;
	int len;

	i = -1;	
	tmp = ft_split(arg, ' ');
	if(f == 1  && len_2d_array((void *)tmp) != 1)
		((t_data *)exec->content)->error = 3;
	while (tmp[++i] && f == 0)
	{
		len = len_2d_array((void **)(((t_data *)exec->content)->args));
		((t_data *)exec->content)->args = (char **)ft_2d_realloc((void **)(((t_data *)exec->content)->args),len + 1);
		((t_data *)exec->content)->args[len] = ft_strdup(tmp[i]);
		free(tmp[i]);
	}
	free(tmp);
}
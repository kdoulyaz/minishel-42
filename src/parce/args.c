/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:54 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/21 17:58:03 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int len_2d_array(void **array)
{
    int i;
    
    i = 0;
	if(!array)
		return (0);
    while (array[i])
        i++;
    return (i);
}

void    fill_args(t_list *exec,t_token *token)
{
    char	*arg;
	int		len;

	len = len_2d_array((void **)(((t_data *)exec->content)->args));
	if(((t_data *)exec->content)->error != 1)
	{
    	arg = ft_strdup(token->value);
    	((t_data *)exec->content)->args = (char **)ft_2d_realloc((void **)(((t_data *)exec->content)->args),len + 1);
	    ((t_data *)exec->content)->args[len] = arg;
	}
}

void **ft_2d_realloc(void **arg,int size)
{
    void **new;
    int j;
    
    j = 0;
    new = (void **)malloc(sizeof(void *) * (size + 1));
    if(arg)
	{
		while (arg[j])
    	{
    	    new[j] = arg[j];
    	    j++;
    	}
	}
    new[j] = NULL;
	new[j + 1] = NULL;
	free(arg);
    return (new);
}

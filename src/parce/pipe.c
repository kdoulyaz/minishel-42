/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:05:12 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/20 20:14:17 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	fill_pipe(t_list *exec, char **envp)
{
	t_list	*new;

	new = init_execution(envp);
	ft_lstadd_back(&exec, new);
}

int	check_qaout(char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(s);
	while (tmp[i])
	{
		if (tmp[i] == '"')
		{
			free(tmp);
			return (2);
		}
		else if (tmp[i] == '\'')
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

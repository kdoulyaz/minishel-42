/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:05:12 by omeslall          #+#    #+#             */
/*   Updated: 2022/10/02 20:15:54 by omeslall         ###   ########.fr       */
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

void	fill_append(t_list *exec, t_token *token)
{
	((t_data *)exec->content)->append = (char **)ft_2d_realloc \
	((void **)(((t_data *)exec->content)->append), \
	len_2d_array((void **)(((t_data *)exec->content)->append)) + 1);
	((t_data *)exec->content)->append[len_2d_array \
	((void **)(((t_data *)exec->content)->append))] = ft_strdup(token->value);
}

void	utils1_qaout(t_list *exec, char **tmp, char **arg)
{
	int		len;
	char	*tmp1;

	len = 0;
	tmp1 = *tmp;
	*tmp = ft_strjoin(*arg, *tmp);
	free(tmp1);
	expand(exec, *tmp, arg);
	expand_split(exec,*arg, 0);
	len = len_2d_array((void **)(((t_data *)exec->content)->args));
	free(*arg);
	if (len > 0)
	{
		*arg = ft_strdup(((t_data *)exec->content)->args[len - 1]);
		free(((t_data *)exec->content)->args[len]);
		free(((t_data *)exec->content)->args[len - 1]);
		((t_data *)exec->content)->args[len - 1] = NULL;
	}
	else
		*arg = ft_strdup("");
}

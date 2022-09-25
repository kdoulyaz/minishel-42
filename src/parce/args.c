/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:54 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 19:36:02 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	len_2d_array(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	utils_fill_args(t_list *exec, char **arg)
{
	((t_data *)exec->content)->args = (char **)ft_2d_realloc((void **) \
	(((t_data *)exec->content)->args), \
	len_2d_array((void **)(((t_data *)exec->content)->args)) + 1);
	((t_data *)exec->content)->args[len_2d_array \
	((void **)(((t_data *)exec->content)->args))] = ft_strdup(*arg);
	free(*arg);
}

void	fill_args(t_list *exec, t_token *token)
{
	char	*arg;
	char	*tmp;

	if (((t_data *)exec->content)->error != 1)
	{
		arg = ft_strdup("");
		if (check_qaout(token->value))
			qaout(exec, token->value, &arg, 0);
		else if (check_if_expand(token->value))
		{
			tmp = arg;
			expand(exec, token->value, &arg);
			free(tmp);
			expand_split(exec, arg, 0);
			free(arg);
			return ;
		}
		else
		{
			free(arg);
			arg = ft_strdup(token->value);
		}
		utils_fill_args(exec, &arg);
	}	
}

void	**ft_2d_realloc(void **arg, int size)
{
	void	**new;
	int		j;

	j = 0;
	new = (void **)malloc(sizeof(void *) * (size + 1));
	if (arg)
	{
		while (arg[j])
		{
			new[j] = ft_strdup(arg[j]);
			free(arg[j]);
			j++;
		}
	}
	new[j] = NULL;
	new[j + 1] = NULL;
	free(arg);
	return (new);
}

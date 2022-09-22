/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:30:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/20 20:17:59 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	qaout_in_redi(t_token *token, t_list *exec, char **arg, int i)
{
	int		j;
	char	*tmp;
	char	*value;

	value = ft_strdup(token->value);
	j = 0;
	if ((int)ft_strlen(value) <= i)
	{
		position_quote(value, 1);
		free(token->value);
		token->value = ft_strdup(*arg);
		free(value);
		free(*arg);
		return ;
	}
	j = position_quote(value, 0);
	tmp = ft_substr(value, i, j + 1);
	if (check_qaout(tmp) == 1)
		single_quote(tmp, arg, 0);
	else if (check_qaout(tmp) == 2)
		double_quote(exec, tmp, arg, 0);
	else if (check_if_expand(tmp) && ((t_data *)(exec->content))->if_hd != 1)
	{
		tmp = ft_strjoin(*arg, tmp);
		expand(tmp, arg);
		expand_split(exec, *arg, 1);
		if (((t_data *)exec->content)->error == 3)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(value, 2);
			ft_putstr_fd(": ambiguous redirect \n", 2);
			free(tmp);
			free(value);
			free(*arg);
			return ;
		}
	}
	else
		*arg = ft_strjoin(*arg, tmp);
	free(tmp);
	free(value);
	qaout_in_redi(token, exec, arg, j + 1);
}

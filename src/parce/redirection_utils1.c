/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:24:37 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/25 01:25:54 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils2_qaout_in_redi(char **tmp, char **arg, t_list *exec)
{
	if (check_qaout(*tmp) == 1)
		single_quote(*tmp, arg, 0);
	else if (check_qaout(*tmp) == 2)
		double_quote(exec, *tmp, arg, 0);
}

void	utils3_qaout_in_redi(char **tmp, char **arg, t_list *exec)
{
	char	*tmp1;

	tmp1 = *tmp;
	*tmp = ft_strjoin(*arg, *tmp);
	free(tmp1);
	expand(exec, *tmp, arg);
	expand_split(exec, *arg, 1);
}

void	utils4_qaout_in_redi(char **tmp, char **value)
{
	free(*tmp);
	free(*value);
}

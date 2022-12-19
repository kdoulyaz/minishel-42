/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:30:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/10/02 19:59:58 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils_qaout_in_redi(t_token *token, char **arg, char **value)
{
	position_quote(*value, 1);
	free(token->value);
	token->value = ft_strdup(*arg);
	free(*value);
	free(*arg);
}

void	utils1_qaout_in_redi(char **arg, char **value, char **tmp \
, t_token *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*value, 2);
	ft_putstr_fd(": ambiguous redirect \n", 2);
	free(*tmp);
	free(*value);
	free(token->value);
	token->value = ft_strdup("");
	free(*arg);
}

void	qaout_in_redi(t_token *token, t_list *exec, char **arg, int i)
{
	int		j;
	char	*tmp;
	char	*value;

	value = ft_strdup(token->value);
	j = 0;
	if ((int)ft_strlen(value) <= i)
	{
		utils_qaout_in_redi(token, arg, &value);
		return ;
	}
	j = position_quote(value, 0);
	tmp = ft_substr(value, i, j);
	utils2_qaout_in_redi(&tmp, arg, exec);
	if (check_if_expand(tmp) && check_qaout(tmp) == 0 \
	&& ((t_data *)(exec->content))->if_hd != 1)
	{
		utils3_qaout_in_redi(&tmp, arg, exec);
		if (((t_data *)exec->content)->error == 1)
			return (utils1_qaout_in_redi(arg, &value, &tmp, token));
	}
	else if (check_qaout(tmp) == 0)
		*arg = ft_strjoin(*arg, tmp);
	utils4_qaout_in_redi(&tmp, &value);
	qaout_in_redi(token, exec, arg, j);
}

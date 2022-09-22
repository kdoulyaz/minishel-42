/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:15:15 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/22 17:47:41 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_acceptable(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

int	check_error(char *arg)
{
	int	i;

	if (ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
		return (1);
	i = 1;
	while (arg[i])
	{
		if (!is_acceptable(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_char_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
}

void	error_unset(char *name)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_glob.g_exit_status = 1;
}

char	*get_variable_name(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * get_char_index(str, '=') + 1);
	if (!tmp)
		return (NULL);
	while (++i < get_char_index(str, '='))
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}

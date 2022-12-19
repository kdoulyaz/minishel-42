/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 03:05:33 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/29 17:07:36 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils_handle_errors(char *argv, size_t *i, size_t *j)
{
	if (argv[*i] == '"' || argv[*i] == 39)
	{
		*j = *i + 1;
		while (argv[*j] != argv[*i])
			*j += 1;
		*i = *j;
	}
}

void	path_err(void)
{
	write(2, "path dosn't exist\n", 18);
	exit(127);
}

void	skip_in_qaout(char *argv, int *i)
{
	int	j;

	j = 0;
	if (argv[*i] == '"' || argv[*i] == 39)
	{
		j = *i + 1;
		while (argv[j] != argv[*i])
			j += 1;
		*i = j;
	}
}

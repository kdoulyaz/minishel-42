/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 05:14:19 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/20 15:52:42 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_cmd(char **args)
{
	char *new_path;

	new_path = getcwd(NULL,0);
	if (args[1] == NULL || (args[1][0] == '~' && ft_strlen(args[1]) == 1))
		new_path = getenv("HOME");
	else if(args[1][0] == '/')
		new_path = args[1];
	else
	{
		new_path = ft_strjoin(new_path,"/");
		new_path = ft_strjoin(new_path,args[1]);
	}
	if (chdir(new_path))
	{
		write(2, "minishell: ", 11);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 28);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:50:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/16 03:45:38 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	g_exit_status;


int main(int ac,char **av,char **envp)
{
	char *line;

	if (!av || !envp)
		return(0);
	g_exit_status = 0;
	if (ac == 1)
	{
		while(1)
		{
			line = readline("minishell:");
			if (!line)
				break;
			if (line && *line)
				add_history (line);
			if(*line)
				parse(line, envp);
		}
	}
	return(g_exit_status);
}
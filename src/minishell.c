/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:50:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/10/02 17:18:04 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	initialiser(void)
{
	init_signal();
	g_glob.g_exit_status = 0;
	g_glob.g_exp = 0;
	g_glob.env = 0;
	g_glob.last = 0;
	g_glob.pwd = NULL;
	g_glob.signal_heredoc = 0;
	g_glob.stop = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	if (!av || !envp)
		return (0);
	initialiser();
	if (ac == 1)
	{
		while (1337)
		{
			line = readline("minishell:");
			if (!line)
				break ;
			if (line && *line)
				add_history (line);
			if (*line)
				parse(line, envp);
			free(line);
		}
	}
	return (g_glob.g_exit_status);
}

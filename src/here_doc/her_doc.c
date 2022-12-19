/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 00:49:30 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/10/03 18:10:12 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

char	*parse_dollar(char *str, int *i, int quote)
{
	int		start;
	char	*new;

	start = *i + 1;
	if (str[start] == '?')
	{
		new = ft_itoa(g_glob.g_exit_status);
		(*i)++;
	}
	else if ((str[start] == '"' || str[start] == '\'') && !quote)
		return (NULL);
	else if (separator(str[start]) || !is_acceptable(str[start]))
		new = ft_strdup("$");
	else
	{
		while (str[*i] && is_acceptable(str[++(*i)]))
			;
		new = new_v(str, *i, start);
		(*i)--;
	}
	return (new);
}

char	*parse_buff(char *buff)
{
	int		i;
	char	*new;
	char	*tmp;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (buff[++i])
	{
		if (buff[i] == '$')
			tmp = parse_dollar(buff, &i, 1);
		else
			tmp = ft_substr2(buff, i, 1);
		new = ft_join(new, tmp);
		free(tmp);
	}
	free (buff);
	return (new);
}

void	open_heredoc(char *value, int expand, t_list *exec)
{
	char	*buff;

	if (pipe(((t_data *)exec->content)->end) == -1)
		perror("minishell: pipe");
	while (42)
	{
		buff = readline("> ");
		if (!buff)
			break ;
		if (!buff[0])
			ft_putstr_fd("\n", ((t_data *)exec->content)->end[1]);
		else if (!ft_strncmp(buff, value, \
				big_len(ft_strlen(value), ft_strlen(buff))))
			break ;
		if (expand == 1)
			buff = parse_buff(buff);
		ft_putstr_fd(buff, ((t_data *)exec->content)->end[1]);
		ft_putstr_fd("\n", ((t_data *)exec->content)->end[1]);
		free(buff);
	}
	free(buff);
	close(((t_data *)exec->content)->end[1]);
}

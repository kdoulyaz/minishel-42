/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 00:54:35 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/10/02 17:21:48 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

char	*exp_dollar(char *str, char **env)
{
	int		i;
	int		len;
	int		slen;
	int		tlen;
	char	*tmp;

	i = -1;
	slen = ft_strlen(str);
	while (env[++i])
	{
		tmp = g_v_n(env[i]);
		if (!tmp)
			return (NULL);
		tlen = ft_strlen(tmp);
		len = ((tlen >= slen) * tlen) + ((tlen < slen) * slen);
		if (ft_strncmp(tmp, str, len) == 0)
		{
			free(tmp);
			return (ft_strdup(env[i] + g_index(env[i], '=') + 1));
		}
		free(tmp);
	}
	return (NULL);
}

char	*new_v(char *str, int i, int start)
{
	char	*tmp;
	char	*new;

	tmp = ft_substr2(str, start, i - start);
	if (!tmp[0])
	{
		free(tmp);
		return (NULL);
	}
	else
		new = exp_dollar(tmp, g_glob.envp);
	free(tmp);
	return (new);
}

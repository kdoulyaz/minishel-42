/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:21:14 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/30 19:23:01 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdio.h>

static int	get_count(char const *s, char d)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == d)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != d)
				i++;
		}
	}
	return (count);
}

static char	*ft_word_cpy(char *word, char const *s, int j, int word_len)
{
	int	i;

	i = 0;
	while (word_len > 0)
	{
		word[i] = s[j - word_len];
		word_len--;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_split_free(char **str, int word_num)
{
	int	i;

	i = 0;
	while (i < word_num)
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	**ft_split2(char **str, char const *s, char c, int word_num)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (s[j] && i < word_num)
	{
		word_len = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			word_len++;
			j++;
		}
		str[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!str[i])
			return (ft_split_free(str, i));
		ft_word_cpy(str[i], s, j, word_len);
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		word_num;

	if (!s)
		return (NULL);
	word_num = get_count(s, c);
	str = (char **)malloc(sizeof(char *) * (word_num + 1));
	if (!str)
		return (NULL);
	ft_split2(str, s, c, word_num);
	return (str);
}
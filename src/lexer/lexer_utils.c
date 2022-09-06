/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:16:02 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/13 18:54:27 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int		is_a_special_char(char c)
{
    if (c == ' ' || c == '\t' || c == '|' || c == '\0' 
    || c == '>' || c == '<')
        return (1);
    return (0);
}

int get_type(char *value)
{
    if (ft_strequ(value, ">"))
        return (R_REDIRECTION);
    else if (ft_strequ(value, "<"))
        return (L_REDIRECTION);
    else if (ft_strequ(value, "|"))
        return (PIPE);
    return (ARG);
}

void    lexer_skip_whitespaces(t_lexer *lexer)
{
    while (lexer->c == ' ' || lexer->c == '\t')
    {
        lexer_advance(lexer);
        lexer->j = lexer->i;    
    }
}

int ft_strequ(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (0);
    if (ft_strcmp(s1, s2) == 0)
        return (1);
    return (0);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0')
        i++;
    return (s1[i] - s2[i]);
}
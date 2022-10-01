/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:17:06 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/27 23:43:33 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->e_type = type;
	return (token);
}

t_token	*fill_token(t_lexer *lexer)
{
	t_token	*token;
	char	*value;
	int		type;

	token = NULL;
	value = ft_substr(lexer->line, lexer->j, lexer->i);
	if (*value)
	{
		type = get_type(value);
		token = init_token(value, type);
		lexer->j = lexer->i;
		return (token);
	}
	free(value);
	return (NULL);
}

t_token	*arg_token(t_lexer *lexer)
{
	char	c;

	while (!is_a_special_char(lexer->c))
	{
		if (lexer->c == '"' || lexer->c == '\'')
		{
			c = lexer->c;
			run_qouate(lexer, &c);
		}
		lexer_advance(lexer);
	}
	return (fill_token(lexer));
}

void	run_qouate(t_lexer *lexer, char *c)
{
	lexer_advance(lexer);
	while (lexer->c != *c)
	{
		lexer_advance(lexer);
	}	
}

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

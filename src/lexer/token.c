#include"../../include/minishell.h"

t_token *init_token(char *value, int type)
{
    t_token *token;
    
    token = ft_calloc(1,sizeof(t_token));
    token->value = value;
    token->type = type;
    return(token);
}

t_token *fill_token(t_lexer *lexer)
{
    t_token *token = NULL;
    char    *value;
    int     type;
    
    value = ft_substr(lexer->line, lexer->j, lexer->i);
    if (*value)
    {
        type = get_type(value);
        token = init_token(value, type);
        lexer->j = lexer->i;
        return (token);
    }
    return(NULL);
}

t_token *arg_token(t_lexer *lexer)
{    
	char	c;

    while (!is_a_special_char(lexer->c))
	{
		if (lexer->c == '"' || lexer->c == '\'')
		{
			c = lexer->c;
			run_qouate(lexer,&c);
		}
        lexer_advance(lexer);
	}
    return(fill_token(lexer));
}

void	run_qouate(t_lexer *lexer,char *c)
{
	lexer_advance(lexer);
	while (lexer->c !=  *c)
	{
		lexer_advance(lexer);
	}	
}

void    free_token(t_token *token)
{
    free(token->value);
    free(token);
}
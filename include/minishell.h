/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:51:19 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/16 05:01:19 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <signal.h>

typedef struct s_token
{
    char *value;
    enum
    {
        ARG,
        R_REDIRECTION = '>',
        L_REDIRECTION = '<',
        PIPE = '|',
    } type;
    
}        t_token;

typedef struct t_lexer
{
    char *line;
    size_t len_line;
    char c;
    unsigned int i;
	unsigned int j;
}       t_lexer;

typedef struct s_data
{
    char 	**args;
	char	**env;
    int 	error;
	char	*inf;
	int 	*infiles;
	int 	n_infiles;
	char	**outfiles;
	char 	**append;
}       t_data;


t_lexer	*init_lexer(char *line);
void	start_exec(t_list *exec);
void	lexer_advance(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
t_token	*init_token(char *value,int type);
t_token	*fill_token(t_lexer *lexer);
int		get_type(char *value);
int		is_a_special_char(char c);
int		parse(char *line, char **envp);
int		ft_strcmp(char *s1, char *s2);
int		ft_strequ(char *s1, char *s2);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token	*arg_token(t_lexer *lexer);
void	run_qouate(t_lexer *lexer,char *c);
void    free_token(t_token *token);
t_list	*init_execution();
t_data	*init_data();
void	free_token(t_token *token);
void    fill_args(t_list *exec,t_token *token);
void	**ft_2d_realloc(void **arg,int size);
int		len_2d_array(void **array);
void	fill_pipe(t_list *exec);
void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer);
void	fill_infile(t_list *exec, t_token *token);
int		*ft_int_realloc(int *ptr, int size);
void	fill_outfile(t_list *exec, t_token *token);
void	fill_append(t_list *exec, t_token *token);
int		handle_errors(char *argv);
int		bulitin(t_list *exec);
int		pwd_cmd(void);
int		execute_bulitings(t_list *exec);

#endif    
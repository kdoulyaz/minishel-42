/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:51:19 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/07 00:54:02 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>

typedef struct s_glob
{
    int	    g_exit_status;
    int     g_child;
    int     g_exp;
    int     g_env;
    char	**envp;
    int     built;
    char	**exp;
    int     signal_heredoc;
    int     signalchild;
    int     breaker;
    int     signalqiut;
    int     pid;
    int     lst_size;
	pid_t	p[2];
	int		tmpin;
	int		tmpout;
	int		copy_fd;
}               t_glob;
t_glob          g_glob;


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
    int 	error;
	char	*inf;
	int 	*infiles;
	int 	n_infiles;
	char	**outfiles;
	char 	**append;
    char    **envp;
}       t_data;

t_data	g_data;

// t_lexer	*init_lexer(char *line);
// void	lexer_advance(t_lexer *lexer);
// t_token	*get_next_token(t_lexer *lexer);
// t_token	*init_token(char *value,int type);
// t_token	*fill_token(t_lexer *lexer);
// int		get_type(char *value);
// int		is_a_special_char(char c);
// int		parse(char *line, char **envp);
// int		ft_strcmp(char *s1, char *s2);
// int		ft_strequ(char *s1, char *s2);
// void	lexer_skip_whitespaces(t_lexer *lexer);
// t_token	*arg_token(t_lexer *lexer);
// void	run_qouate(t_lexer *lexer,char *c);
// void    free_token(t_token *token);
// t_list	*init_execution(char **envp);
// t_data	*init_data(char **envp);
// int		check_qaout(char *s);
// void	single_quote(char *value,char **arg,int i);
// int		position_quote_s(char *s,int f);
// int		position_quote_d(char *s, int f);
// void	double_quote(t_list *exec,char *value,char **arg,int i);
// void	qaout(t_list *exec, char *value, char **arg, int i);
// int		position_quote(char *s, int f);
// void    fill_args(t_list *exec,t_token *token);
// void	**ft_2d_realloc(void **arg,int size);
// int		len_2d_array(void **array);
// void	fill_pipe(t_list *exec, char **envp);
// void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer);
// void	fill_infile(t_list *exec, t_token *token);
// int		*ft_int_realloc(int *ptr, int size);
// void	fill_outfile(t_list *exec, t_token *token);
// void	fill_append(t_list *exec, t_token *token);
// int		handle_errors(char *argv);
// int 	check_if_expand(char *s);
// void	expand(t_list *exec,char *value,char **arg);
// char	*fill_expand(t_list *exec,char *value);
// void	expand_split(t_list *exec,char *arg);
// //-----------------------------------------------------
// int		bulitin(t_list *exec);
// void	error_export(char *name);
// int		pwd_cmd(char **envp);
// int		execute_bulitings(t_list *exec, char **envp);
// int		cd_cmd(char **args);
// void	start_exec(t_list *exec, char **eenv);
// void	cmd_err(char *cmd);
// void	path_err(void);
// char	*find_path(char *cmd, char **env);
// void	open_out(t_list *exec, int *fdout);
// int		echo_cmd(char **args);
// int 	exit_cmd(char **args);
// int	    count_args(char **args);
// char    **create_envp(char **envp);
// int	    count_args(char **args);
// char	**add_env(char **strs, char *arg);
// int     env_cmd(t_list *exec);
// void	init_signal(void);
t_lexer	*init_lexer(char *line);
void	lexer_advance(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
t_token	*init_token(char *value,int type);
t_token	*fill_token(t_lexer *lexer);
int		get_type(char *value);
int		is_a_special_char(char c);
int	    parse(char *line, char **envp);
int		ft_strcmp(char *s1, char *s2);
int		ft_strequ(char *s1, char *s2);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token	*arg_token(t_lexer *lexer);
void	run_qouate(t_lexer *lexer,char *c);
void    free_token(t_token *token);
t_list	*init_execution(char **envp);
t_data	*init_data(char **envp);
void	free_token(t_token *token);
void    fill_args(t_list *exec,t_token *token);
void	**ft_2d_realloc(void **arg,int size);
int		len_2d_array(void **array);
void	fill_pipe(t_list *exec, char **envp);
void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer);
void	fill_infile(t_list *exec, t_token *token);
int		*ft_int_realloc(int *ptr, int size);
void	fill_outfile(t_list *exec, t_token *token);
void	fill_append(t_list *exec, t_token *token);
int		handle_errors(char *argv);
int		bulitin(t_list *exec);
int	    pwd_cmd(void);
int	    execute_bulitings(t_list *exec);
int		cd_cmd(char **args);
void	start_exec(t_list *exec, char **eenv);
void	cmd_err(char *cmd);
void	path_err(void);
char	*find_path(char *cmd, char **env);
void	open_out(t_list *exec, int *fdout);
int    echo_cmd(char **args);
int 	exit_cmd(char **args);
int	    count_args(char **args);
char    **create_envp(char **envp);
int	    count_args(char **args);
char	**add_env(char **strs, char *arg);
int     env_cmd(t_list *exec);
int 	unset_cmd(char **args);
int	    export_cmd(t_list *exec);
char	**creat_export(char **env);
char	*ft_join(char *s1, char *s2);
char	*get_variable_name(char *str);
int	    get_char_index(char *str, char c);
int	    check_error(char *arg);
int	    get_index(char *str, char c);
int	    big_len(int s1, int s2);
void	error_export(char *name);
char	*get_new_line(char *name, char *value);
char	*get_name(char *str);
int	    is_variable_exist(char *name);
int	    is_acceptable(char c);
void	error_unset(char *name);
char	*fill_expand(char *value);
int     check_if_expand(char *s);
void	expand(char *value,char **arg);
int	    position_quote(char *s, int f);
void	qaout(t_list *exec, char *value, char **arg, int i);
int 	check_qaout(char *s);
void	handlear(int signal);
void	init_signal(void);
void	clean_nood(t_list	*exec);
void	expand_split(t_list *exec,char *arg,int f);
void	qaout_in_redi(t_token *token,t_list *exec,char **arg,int i);
void	parse_arg_redi(t_token *token,t_list *exec);
void	single_quote(char *value,char **arg,int i);
void	double_quote(t_list *exec,char *value,char **arg,int i);
int	    *add_pid(int *pids, int pid);
void	update_env(char *old_pwd, char *new_path);
int		err_inf(t_list *exec);
void	ft_dup(int fd, int end);
void	piping(pid_t *p);
void	waiting(int tmpin, int tmpout, t_list *lst);

#endif
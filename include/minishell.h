/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:51:19 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/25 05:43:11 by kdoulyaz         ###   ########.fr       */
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
	int		g_exit_status;
	int		g_child;
	int		g_exp;
	int		h_flag;
	int		g_env;
	char	**envp;
	int		built;
	int		i;
	int		j;
	char	**exp;
	char	*newpwd;
	int		signal_heredoc;
	int		signalchild;
	int		stop;
	int		signalqiut;
	int		pid;
	int		fdout;
	int		lst_size;
	int		tmpin;
	int		tmpout;
	int		end[2];
	char	*new_path;
	int		copy_fd;
	int		input;
	int		dollar;
	char	*pwd;
	int		flag;
	int		env;
	char	*old_pwd;
}				t_glob;
t_glob			g_glob;

typedef struct s_token
{
	char	*value;
	enum
	{
		ARG,
		R_REDIRECTION = '>',
		L_REDIRECTION = '<',
		PIPE = '|',
	}			e_type;
}				t_token;

typedef struct t_lexer
{
	char			*line;
	size_t			len_line;
	char			c;
	unsigned int	i;
	unsigned int	j;
}				t_lexer;

typedef struct s_data
{
	char	**args;
	int		error;
	int		if_hd;
	char	*inf;
	int		*infiles;
	int		n_infiles;
	char	**outfiles;
	char	**append;
	char	**hd;
	char	**envp;
}				t_data;

t_lexer	*init_lexer(char *line);
void	lexer_advance(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
t_token	*init_token(char *value, int type);
t_token	*fill_token(t_lexer *lexer);
int		get_type(char *value);
int		is_a_special_char(char c);
int		parse(char *line, char **envp);
int		ft_strcmp(char *s1, char *s2);
int		ft_strequ(char *s1, char *s2);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token	*arg_token(t_lexer *lexer);
void	run_qouate(t_lexer *lexer, char *c);
void	free_token(t_token *token);
t_list	*init_execution(char **envp);
t_data	*init_data(char **envp);
int		check_qaout(char *s);
void	single_quote(char *value, char **arg, int i);
int		position_quote_s(char *s, int f);
int		position_quote_d(char *s, int f);
void	double_quote(t_list *exec, char *value, char **arg, int i);
void	qaout(t_list *exec, char *value, char **arg, int i);
int		position_quote(char *s, int f);
void	fill_args(t_list *exec, t_token *token);
void	**ft_2d_realloc(void **arg, int size);
int		len_2d_array(void **array);
void	fill_pipe(t_list *exec, char **envp);
void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer);
void	fill_infile(t_list *exec, t_token *token);
int		*ft_int_realloc(int *ptr, int size);
void	fill_outfile(t_list *exec, t_token *token);
void	fill_append(t_list *exec, t_token *token);
int		handle_errors(char *argv);
int		check_if_expand(char *s);
void	expand(t_list *exec, char *value, char **arg);
char	*fill_expand(t_list *exec, char *value);
void	expand_split(t_list *exec, char *arg, int f);
void	qaout_in_redi(t_token *token, t_list *exec, char **arg, int i);
void	parse_arg_redi(t_token *token, t_list *exec);
void	free_exec(t_list *exec);
int		red_error(int *i, int *j, char *argv);
char	quotes_exist(char *argv, size_t *i);
void	expand_exit_status(char **tmp, int *i);
void	utils_expand(t_list *exec, char *value, char **tmp, int *i);
void	utils2_qaout_in_redi(char **tmp, char **arg, t_list *exec);
void	utils3_qaout_in_redi(char **tmp, char **arg, t_list *exec);
void	utils4_qaout_in_redi(char **tmp, char **value);
void	utils1_qaout(t_list *exec, char **tmp, char **arg);
int		utils3_position_quote(int j, int *i, int *q, char *tmp);
void	utils1_position_quote(int f, int *i, int *q, char *tmp);
int		utils2_position_quote(int j, int *i, int *q, char *tmp);
int		ft_skip_whitespace(char *av, int *i);
int		red_error(int *i, int *j, char *argv);
char	quotes_exist(char *argv, size_t *i);
int		handle_quotes(char *s);
int		ft_cmp(char *s, char c);
void	utils_handle_errors(char *argv, size_t *i, size_t *j);

//-----------------------------------------------------

int		bulitin(t_list *exec);
int		pwd_cmd(void);
int		execute_bulitings(t_list *exec, int mode);
int		cd_cmd(char **args);
void	start_exec(t_list *exec);
void	cmd_err(char *cmd);
void	path_err(void);
char	*find_path(char *cmd, char **env);
void	open_out(t_list *exec, int i);
int		echo_cmd(char **args);
int		exit_cmd(char **args);
int		count_args(char **args);
char	**create_envp(char **envp);
int		count_args(char **args);
char	**add_env(char **strs, char *arg);
int		env_cmd(void);
int		unset_cmd(char **args);
int		export_cmd(t_list *exec);
char	**creat_export(char **env);
char	*ft_join(char *s1, char *s2);
char	*g_v_n(char *str);
int		get_index(char *str, char c);
int		check_error(char *arg);
int		g_index(char *str, char c);
int		big_len(int s1, int s2);
void	error_export(char *name);
char	*get_new_line(char *name, char *value);
char	*get_name(char *str);
int		is_variable_exist(char *name);
int		is_acceptable(char c);
void	error_unset(char *name);
void	handlear(int signal);
void	init_signal(void);
void	clean_nood(t_list	*exec);
int		*add_pid(int *pids, int pid);
void	update_env(char *old_pwd, char *new_path);
void	waiting(t_list *lst);
void	ft_dup(int fd, int end);
int		child_bulitin(t_list *exec);
int		child_execute_bulitings(t_list *exec);
void	piping(pid_t *p);
int		err_inf(t_list *exec);
int		open_out1(t_list *exec, int i);
char	*ft_join1(char *s1, char *s2);
void	norm(t_list *exec, int *p, int copy_fd);
void	ree(t_list *exec);
int		err_fork(void);
void	initialise(void);
char	*ft_getenv(char *str);
void	error_msg(char *str, int err);
void	getcwd_error(int err, char *path);
int		separator(char c);
char	*new_v(char *str, int i, int start);
void	open_heredoc(char *value, int expand);
int		cd_cmd1(char **args);
void	cd_err(void);
void	update_env1(char *old_pwd);

#endif
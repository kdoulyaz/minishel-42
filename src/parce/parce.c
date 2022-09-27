/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:46:55 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/25 16:24:36 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	norm1(t_list *exec, char **value, int i)
{
	((t_data *)(exec->content))->if_hd = 1;
	if (check_qaout(((t_data *)exec->content)->hd[i]) == 1)
		single_quote(((t_data *)exec->content)->hd[i], value, 0);
	else if (check_qaout(((t_data *)exec->content)->hd[i]) == 2)
		double_quote(exec, ((t_data *)exec->content)->hd[i], value, 0);
	((t_data *)(exec->content))->if_hd = 0;
	return (0);
}

void	here_docc(t_list	*exec)
{
	int		expand;
	char	*value;
	int		i;

	i = -1;
	while (((t_data *)exec->content)->hd && ((t_data *)exec->content)->hd[++i])
	{
		expand = 1;
		g_glob.signal_heredoc = 1;
		g_glob.tmpin = dup(0);
		value = ft_strdup("");
		if (check_qaout(((t_data *)exec->content)->hd[i]))
			expand = norm1(exec, &value, i);
		else
		{
			free(value);
			value = ft_strdup(((t_data *)exec->content)->hd[i]);
		}
		if (g_glob.stop == 0)
			open_heredoc(value, expand);
		free (value);
		dup2(g_glob.tmpin, 0);
		close(g_glob.tmpin);
		g_glob.signal_heredoc = 0;
	}
}

void	util_token(t_token **token, t_list *exec, char **envp, t_lexer *lexer)
{
	if ((*token)->e_type == ARG)
		fill_args(ft_lstlast(exec), *token);
	else if ((*token)->e_type == L_REDIRECTION
		|| (*token)->e_type == R_REDIRECTION)
		fill_redirections(ft_lstlast(exec), token, lexer);
	else if ((*token)->e_type == PIPE)
		fill_pipe(exec, envp);
}

int	parse(char *line, char **envp)
{
	t_token	*token;
	t_lexer	*lexer;
	t_list	*exec;

	if (!handle_errors(line))
		return (0);
	lexer = init_lexer(line);
	token = get_next_token(lexer);
	exec = init_execution(envp);
	while (token)
	{
		util_token(&token, exec, envp, lexer);
		free_token(token);
		token = get_next_token(lexer);
	}
	here_docc(exec);
	free(lexer);
	start_exec(exec);
	free_exec(exec);
	return (g_glob.g_exit_status);
}

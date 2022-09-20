/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:46:55 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/19 23:11:17 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	printer(t_list *exec)
{
	int i;
	i = 0;
	while (exec)
	{	
		printf("========================================================================================\n\n");

		if(((t_data *)exec->content)->args)
		{
			i = 0;
			printf("-----------------args-------------------------\n");
			while(((t_data *)exec->content)->args[i])
			{
					printf("----((t_data *)exec->content)->args[%d]----------->%s\n",i,((t_data *)exec->content)->args[i]);
				i++;
			}
			printf("-----------------args-------------------------\n\n");
		}
		i = 0;
		if(((t_data *)exec->content)->infiles)
		{
			printf("-----------------infiles-------------------------\n");
			while(((t_data *)exec->content)->n_infiles > i)
			{
					printf("---((t_data *)exec->content)->infiles[%d]--->%d\n",i,((t_data *)exec->content)->infiles[i]);
					printf("---((t_data *)exec->content)->inf[%d]--->%s\n",i,((t_data *)exec->content)->inf);
				i++;
			}
			printf("-----------------infiles-------------------------\n\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->outfiles)
		{
			printf("-----------------outfiles-------------------------\n");
			while(((t_data *)exec->content)->outfiles[i])
			{
					printf("---((t_data *)exec->content)->outfiles[%d]--->%s\n",i,((t_data *)exec->content)->outfiles[i]);
				i++;
			}
			printf("-----------------outfiles-------------------------\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->append)
		{
			printf("-----------------append-------------------------\n");
			while(((t_data *)exec->content)->append[i])
			{
					printf("---((t_data *)exec->content)->append[%d]--->%s\n",i,((t_data *)exec->content)->append[i]);
				i++;
			}
			printf("-----------------append-------------------------\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->hd)
		{
			printf("-----------------hd-------------------------\n");
			while(((t_data *)exec->content)->hd[i])
			{
					printf("---((t_data *)exec->content)->hd[%d]--->%s\n",i,((t_data *)exec->content)->hd[i]);
				i++;
			}
			printf("-----------------hd-------------------------\n");
				
		}
		printf("========================================================================================\n");
		exec = exec->next;
	}
}

char	*parse_limiter(char *str, int *expand)
{
	char	q;
	char	*new;
	char	*tmp;
	int		i;
	int		start;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			(*expand) = 0;
			start = i + 1;
			q = str[i];
			while (str[++(i)] && str[i] != q)
				;
			tmp = ft_substr2(str, start, i - start);
		}
		else
			tmp = ft_substr2(str, i, 1);
		new = ft_join(new, tmp);
		free(tmp);
	}
	return (new);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

char	*expand_dollar(char *str, char **env)
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
		tmp = get_variable_name(env[i]);
		if (!tmp)
			return (NULL);
		tlen = ft_strlen(tmp);
		len = ((tlen >= slen) * tlen) + ((tlen < slen) * slen);
		if (ft_strncmp(tmp, str, len) == 0)
		{
			free(tmp);
			return (ft_strdup(env[i] + get_char_index(env[i], '=') + 1));
		}
		free(tmp);
	}
	return (NULL);
}

char	*new_value(char *str, int i, int start)
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
		new = expand_dollar(tmp, g_glob.envp);
	free(tmp);
	return (new);
}

char	*parse_dollar(char *str, int *i, int quote)
{
	int		start;
	char	*new;

	start = *i + 1;
	g_glob.dollar = 1;
	if (str[start] == '?')
	{
		new = ft_itoa(g_glob.g_exit_status);
		(*i)++;
	}
	else if ((str[start] == '"' || str[start] == '\'') && !quote)
		return (NULL);
	else if (is_separator(str[start]) || !is_acceptable(str[start]))
		new = ft_strdup("$");
	else
	{
		while (str[*i] && is_acceptable(str[++(*i)]))
			;
		new = new_value(str, *i, start);
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

void	open_heredoc(char *value, int expand)
{
	char	*buff;

	if (pipe(g_glob.end) == -1)
		perror("minishell: pipe");
	while (42)
	{
		buff = readline("> ");
		if (!buff)
			break ;
		if (!buff[0])
			ft_putstr_fd("\n", g_glob.end[1]);
		else if (!ft_strncmp(buff, value, \
				big_len(ft_strlen(value), ft_strlen(buff))))
			break ;
		if (expand == 1)
			buff = parse_buff(buff);
		ft_putstr_fd(buff, g_glob.end[1]);
		ft_putstr_fd("\n", g_glob.end[1]);
		free(buff);
	}
	free(buff);
	close(g_glob.end[1]);
}

void	here_doc(t_list	*exec)
{
	int		expand;
	char	*value;
	int		i;

	i = -1;
	while (((t_data *)exec->content)->hd && ((t_data *)exec->content)->hd[++i])
	{
		g_glob.signal_heredoc = 1;
		g_glob.tmpin = dup(0);
		expand = 1;
		value = parse_limiter(((t_data *)exec->content)->hd[i], &expand);
		if (g_glob.breaker == 0)
			open_heredoc(value, expand);
		free (value);
		dup2(g_glob.tmpin, 0);
		close(g_glob.tmpin);
		g_glob.signal_heredoc = 0;
	}
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
		if (token->type == ARG)
			fill_args(ft_lstlast(exec), token);
		else if (token->type == L_REDIRECTION || token->type == R_REDIRECTION)
			fill_redirections(ft_lstlast(exec), &token, lexer);
		else if (token->type == PIPE)
			fill_pipe(exec, envp);
		free_token(token);
		token = get_next_token(lexer);
	}
	// printer(exec);//$"HOME"
	here_doc(exec);
	free(lexer);
	start_exec(exec);
	free_exec(exec);// return (g_exit_status);
	return (0);
}

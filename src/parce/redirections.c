/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:33:34 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/20 19:52:36 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	fill_heredoc(t_list *exec, t_token **token)
{
	((t_data *)exec->content)->hd = (char **)ft_2d_realloc((void **) \
	(((t_data *)exec->content)->hd), len_2d_array((void **) \
	(((t_data *)exec->content)->hd)) + 1);
	((t_data *)exec->content)->hd[len_2d_array \
	((void **)(((t_data *)exec->content)->hd))] = ft_strdup((*token)->value);
}

void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer)
{
	if ((*token)->type == L_REDIRECTION
		&& ((t_data *)exec->content)->error != 1)
	{
		free_token(*token);
		*token = get_next_token(lexer);
		parse_arg_redi(*token, exec);
		if ((*token)->type == ARG && ((t_data *)exec->content)->error != 1)
			fill_infile(exec, *token);
		else if ((*token)->type == L_REDIRECTION)
		{
			free_token(*token);
			*token = get_next_token(lexer);
			fill_heredoc(exec, token);
		}
	}
	else if ((*token)->type == R_REDIRECTION
		&& ((t_data *)exec->content)->error != 1)
	{
		free_token(*token);
		*token = get_next_token(lexer);
		parse_arg_redi(*token, exec);
		if ((*token)->type == ARG && ((t_data *)exec->content)->error != 1)
			fill_outfile(exec, *token);
		else if ((*token)->type == R_REDIRECTION)
		{
			free_token(*token);
			*token = get_next_token(lexer);
			fill_append(exec, *token);
		}
	}
}

void	parse_arg_redi(t_token *token, t_list *exec)
{
	char	*arg;

	arg = ft_strdup("");
	if (check_qaout(token->value) || check_if_expand(token->value))
		qaout_in_redi(token, exec, &arg, 0);
	else
		free(arg);
}

void	fill_infile(t_list *exec, t_token *token)
{
	int	fd;

	fd = open(token->value, O_RDONLY);
	if (fd == -1)
	{
		((t_data *)exec->content)->inf = ft_strdup(token->value);
		((t_data *)exec->content)->error = 1;
	}
	((t_data *)exec->content)->infiles = ft_int_realloc \
	(((t_data *)exec->content)->infiles, ((t_data *)exec->content)->n_infiles);
	((t_data *)exec->content)->infiles[\
	((t_data *)exec->content)->n_infiles] = fd;
	((t_data *)exec->content)->n_infiles++;
}

void	fill_outfile(t_list *exec, t_token *token)
{
	((t_data *)exec->content)->outfiles = (char **)ft_2d_realloc \
	((void **)(((t_data *)exec->content)->outfiles), \
	len_2d_array((void **)(((t_data *)exec->content)->outfiles)) + 1);
	((t_data *)exec->content)->outfiles[len_2d_array \
	((void **)(((t_data *)exec->content)->outfiles))] = ft_strdup(token->value);
}

void	fill_append(t_list *exec, t_token *token)
{
	((t_data *)exec->content)->append = (char **)ft_2d_realloc \
	((void **)(((t_data *)exec->content)->append), \
	len_2d_array((void **)(((t_data *)exec->content)->append)) + 1);
	((t_data *)exec->content)->append[len_2d_array \
	((void **)(((t_data *)exec->content)->append))] = ft_strdup(token->value);
}

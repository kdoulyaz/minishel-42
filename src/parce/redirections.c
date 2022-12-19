/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:33:34 by omeslall          #+#    #+#             */
/*   Updated: 2022/10/02 20:16:33 by omeslall         ###   ########.fr       */
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

void	utils1_fill_redirections(t_list *exec, t_token **token, t_lexer *lexer)
{
	free_token(*token);
	*token = get_next_token(lexer);
	parse_arg_redi(*token, exec);
	if ((*token)->e_type == ARG && ((t_data *)exec->content)->error != 1)
		fill_infile(exec, *token);
	else if ((*token)->e_type == L_REDIRECTION)
	{
		free_token(*token);
		*token = get_next_token(lexer);
		fill_heredoc(exec, token);
	}
}

void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer)
{
	if ((*token)->e_type == L_REDIRECTION
		&& ((t_data *)exec->content)->error != 1)
		utils1_fill_redirections(exec, token, lexer);
	else if ((*token)->e_type == R_REDIRECTION
		&& ((t_data *)exec->content)->error != 1)
	{
		free_token(*token);
		*token = get_next_token(lexer);
		parse_arg_redi(*token, exec);
		if ((*token)->e_type == ARG && ((t_data *)exec->content)->error != 1)
			fill_outfile(exec, *token);
		else if ((*token)->e_type == R_REDIRECTION)
		{
			free_token(*token);
			*token = get_next_token(lexer);
			parse_arg_redi(*token, exec);
			if (((t_data *)exec->content)->error != 1)
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

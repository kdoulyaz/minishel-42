/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:10:11 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/25 02:15:54 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_isalnum(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	else if ((34 <= c && c <= 90) || (91 <= c && c <= 126) || c == 32
		|| c == '<' || c == '>' || c == '-' || c == 39 || c == '"'
		|| c == '$')
		return (1);
	else
		return (0);
}

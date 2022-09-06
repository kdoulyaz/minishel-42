/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 00:25:57 by omeslall          #+#    #+#             */
/*   Updated: 2021/12/20 18:30:40 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**index;
	t_list	*new;
	t_list	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	index = &new;
	while (temp)
	{
		new = ft_lstnew((f)(temp->content));
		if (!new)
		{
			ft_lstclear(index, del);
			return (NULL);
		}
		temp = temp->next;
		ft_lstadd_back(index, new);
	}
	return (new);
}

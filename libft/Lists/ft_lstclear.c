/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:58:40 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/17 13:30:03 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	{
		if (*lst == 0)
			return ;
		while (*lst)
		{
			next = (*lst)->next;
			if (del)
				del((*lst)->content);
			free(*lst);
			*lst = next;
		}
		*lst = 0;
	}
}

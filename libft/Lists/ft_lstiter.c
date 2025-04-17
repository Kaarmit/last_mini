/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:47:28 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/17 13:30:08 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	{
		while (lst)
		{
			if (f)
				f(lst->content);
			lst = lst->next;
		}
	}
}

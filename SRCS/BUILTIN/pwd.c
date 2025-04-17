/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:53:21 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/11 17:53:59 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	pwd(t_env **lst)
{
	t_env	*curr;

	curr = (*lst);
	while (curr)
	{
		if (ft_strcmp(curr->name, "PWD") == 0)
		{
			ft_putstr_fd(curr->content, 1);
			ft_putstr_fd("\n", 1);
			return ;
		}
		curr = curr->next;
	}
	return ;
}

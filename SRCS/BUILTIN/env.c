/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:24 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/13 10:36:25 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	env(t_env **lst)
{
	t_env	*curr;
	char	*equal;
	char	*complete;

	curr = (*lst);
	if (!(curr))
		return ;
	while (curr)
	{
		if (curr->content)
		{
			equal = ft_strjoin(curr->name, "=");
			complete = ft_strjoin(equal, curr->content);
			free(equal);
			ft_putstr_fd(complete, 1);
			ft_putstr_fd("\n", 1);
			free(complete);
		}
		curr = curr->next;
	}
	return ;
}

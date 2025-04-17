/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:04 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/10 17:50:04 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	set_cmd(t_chunk *current, t_token **start)
{
	current->cmd = ft_strdup((*start)->token);
	if (!current->cmd)
		return (-1);
	*start = (*start)->next;
	return (0);
}

int	process_word(t_chunk *current, t_token **start)
{
	int	i;

	i = 0;
	if (!current->cmd)
		return (set_cmd(current, start));
	if (!current->args)
		return (set_args(start, current));
	return (add_more_args(start, current, i));
}

int	handle_word(t_chunk **chunk_lst, t_token **token_lst)
{
	t_token	*start;
	t_chunk	*current;

	start = *token_lst;
	while (start && start->type == ARG)
	{
		current = lst_last_chunk(*chunk_lst);
		if (!current)
			return (-1);
		if (!start->prev || start->prev->type == PIPE || !current->cmd)
		{
			if (set_cmd(current, &start) == -1)
				return (-1);
		}
		else if (process_word(current, &start) == -1)
			return (-1);
	}
	*token_lst = start;
	return (0);
}

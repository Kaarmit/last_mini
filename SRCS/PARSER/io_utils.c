/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:13 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/10 17:50:13 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	init_io_struct(t_io_chunk *io)
{
	io->path = NULL;
	io->next = NULL;
	io->prev = NULL;
	io->here_doc = 0;
	io->type = -1;
}

int	init_io_chunk(t_chunk *chunk)
{
	t_io_chunk	*temp;

	if (!chunk->io_handle)
	{
		chunk->io_handle = (t_io_chunk *)malloc(sizeof(t_io_chunk));
		if (!(chunk->io_handle))
			return (0);
		init_io_struct(chunk->io_handle);
	}
	else
	{
		temp = chunk->io_handle;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_io_chunk *)malloc(sizeof(t_io_chunk));
		if (!temp->next)
			return (0);
		init_io_struct(temp->next);
		temp->next->prev = temp;
	}
	return (1);
}

void	lstdelone_io_list(t_io_chunk *io_node, void (*del)(void *))
{
	if (io_node->path)
		(*del)(io_node->path);
	(*del)(io_node);
}

void	lstclear_io_list(t_io_chunk **io_list, void (*del)(void *))
{
	t_io_chunk	*temp;

	temp = NULL;
	while (*io_list)
	{
		temp = (*io_list)->next;
		lstdelone_io_list(*io_list, del);
		*io_list = temp;
	}
}

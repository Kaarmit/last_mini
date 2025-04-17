/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:49:45 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/10 17:49:45 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	io_type(t_type type, t_io_chunk *io)
{
	if (type == INPUT)
		return (IO_IN);
	else if (type == HEREDOC)
	{
		io->here_doc = 1;
		return (IO_HEREDOC);
	}
	else if (type == TRUNC)
		return (IO_OUT);
	else if (type == APPEND)
		return (IO_APPEND);
	else
		return (0);
}

int	is_redirection(t_type type)
{
	if (type == TRUNC || type == APPEND || type == INPUT || type == HEREDOC)
		return (1);
	return (0);
}

static t_token	*get_next_token(t_token *token)
{
	if (token->next->next)
		return (token->next->next);
	else
		return (token->next);
}

int	handle_redirection(t_chunk **chunk_lst, t_token **token_lst, t_type type)
{
	t_chunk		*chunk;
	t_token		*start;
	t_io_chunk	*last_io;

	start = *token_lst;
	chunk = lst_last_chunk(*chunk_lst);
	init_io_chunk(chunk);
	last_io = chunk->io_handle;
	if (!(last_io))
		return (-1);
	while (last_io && last_io->next)
		last_io = last_io->next;
	while (start->type <= PIPE)
		start = start->next;
	last_io->type = io_type(type, last_io);
	if (last_io->here_doc != 1)
		last_io->path = ft_strdup(start->next->token);
	if (!last_io->path)
		return (-1);
	start = get_next_token(start);
	*token_lst = start;
	return (0);
}

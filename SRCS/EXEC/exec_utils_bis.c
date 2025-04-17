/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:14:00 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 17:51:29 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	redir_in(t_io_chunk *io)
{
	int	fdi;

	if (!io->path)
	{
		printf("no infile\n");
		return ;
	}
	fdi = open(io->path, O_RDONLY);
	if (fdi == -1)
	{
		perror("open infile");
		exit(1);
	}
	dup2(fdi, STDIN_FILENO);
	close(fdi);
}

void	redir_out(t_io_chunk *io)
{
	int	fdo;

	if (!io->path)
	{
		printf("no infile\n");
		return ;
	}
	fdo = open(io->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdo == -1)
	{
		perror("open outfile");
		exit(1);
	}
	dup2(fdo, STDOUT_FILENO);
	close(fdo);
}

void	redir_append(t_io_chunk *io)
{
	int	fdo;

	if (!io->path)
	{
		printf("no infile\n");
		return ;
	}
	fdo = open(io->path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fdo == -1)
	{
		perror("open append");
		exit(1);
	}
	dup2(fdo, STDOUT_FILENO);
	close(fdo);
}

void	redir(t_chunk *chunk)
{
	t_io_chunk	*io;

	io = chunk->io_handle;
	if (!io)
		return ;
	while (io)
	{
		if (io->type == IO_IN)
			redir_in(io);
		else if (io->type == IO_OUT)
			redir_out(io);
		else if (io->type == IO_APPEND)
			redir_append(io);
		io = io->next;
	}
	return ;
}

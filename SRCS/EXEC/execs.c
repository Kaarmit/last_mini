/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:59 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/17 20:19:39 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	ft_close_all(int fd[3])
{
	char	buf;
	int		i;

	i = 3;
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	while (i < 150)
	{
		if (read(i, &buf, 0) != -1)
			close(i);
		i++;
	}
}

// void	processs(t_data *data, t_chunk *chunk, int fd[3])
// {
// 	if (!chunk->prev)
// 		dup2(fd[1], STDOUT_FILENO);
// 	if (!chunk->next)
// 		dup2(fd[2], STDIN_FILENO);
// 	else if (chunk->next && chunk->prev)
// 	{
// 		dup2(fd[2], STDIN_FILENO);
// 		dup2(fd[1], STDOUT_FILENO);
// 	}
// 	ft_close_all(fd);
// 	if (!chunk->args)
// 	{
// 		redir(chunk);
// 		close(data->stdin);
// 		close(data->stdout);
// 		free_data_exec(data);
// 		rl_clear_history();
// 		exit(0);
// 	}
// 	else if (is_builtin(chunk->cmd))
// 	{
// 		redir(chunk);
// 		do_builtin(data, chunk, chunk->cmd);
// 		redir(chunk);
// 		close(data->stdin);
// 		close(data->stdout);
// 		free_data_exec(data);
// 		rl_clear_history();
// 		exit(0);
// 	}
// 	if (is_dot(data->chunk->cmd))
// 		return (free_data_exec(data));
// 	if (is_dir(data->chunk->cmd))
// 		return (free_data_exec(data));
// 	redir(chunk);
// 	exec_cmd(data, chunk->args, data->envcpy);
// }

void	special_cases(t_data *data, t_chunk *chunk)
{
	if (!chunk->args)
	{
		redir(chunk);
		clean_program(data);
		exit(single_exit_s(0, RETRIEVE));
	}
	else if (is_builtin(chunk->cmd))
	{
		redir(chunk);
		do_builtin(data, chunk, chunk->cmd);
		redir(chunk);
		clean_program(data);
		rl_clear_history();
		exit(single_exit_s(0, RETRIEVE));
	}
	if (is_dot(data->chunk->cmd))
		return (clean_program_exec(data));
	if (is_dir(data->chunk->cmd))
		return (clean_program_exec(data));
}

void	processs(t_data *data, t_chunk *chunk, int fd[3])
{
	char	*path;

	if (!chunk->prev)
		dup2(fd[1], STDOUT_FILENO);
	if (!chunk->next)
		dup2(fd[2], STDIN_FILENO);
	else if (chunk->next && chunk->prev)
	{
		dup2(fd[2], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	ft_close_all(fd);
	special_cases(data, chunk);
	path = find_path(chunk->cmd, data);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(chunk->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_program_exec(data);
	}
	redir(chunk);
	execve(path, chunk->args, data->envcpy);
	perror("execve");
	free(path);
	free_data_exec(data);
	exit(127);
}


void	waitit(t_data *data)
{
	t_chunk	*chunk;

	chunk = (data->chunk);
	while (chunk)
	{
		waitpid(chunk->pid, NULL, 0);
		chunk = chunk->next;
	}
}

void	swap_pipes(int fd[3])
{
	dup2(fd[0], fd[2]);
	close(fd[0]);
	close(fd[1]);
}

t_chunk *get_last_chunk(t_chunk *chunk)
{
	while (chunk && chunk->next)
		chunk = chunk->next;
	return chunk;
}

// void execs(t_data *data, t_chunk **chunk_lst)
// {
// 	int		fd[3];
// 	t_chunk	*chunk;

// 	data->stdin = dup(STDIN_FILENO);
// 	data->stdout = dup(STDOUT_FILENO);
// 	fd[2] = dup(STDIN_FILENO);

// 	chunk = get_last_chunk(*chunk_lst);

// 	while (chunk)
// 	{
// 		if (pipe(fd) != 0)
// 			err_pipe();
// 		chunk->pid = fork();
// 		if (chunk->pid == -1)
// 			err_fork();
// 		if (!chunk->pid)
// 			processs(data, chunk, fd);
// 		swap_pipes(fd);
// 		chunk = chunk->prev;
// 	}
// 	close(fd[2]);
// 	waitit(data);
// }

// void	processs(t_data *data, t_chunk *chunk, int fd[3])
// {
// 	if (!chunk->prev)
// 		dup2(fd[1], STDOUT_FILENO);
// 	if (!chunk->next)
// 		dup2(fd[2], STDIN_FILENO);
// 	else if (chunk->next && chunk->prev)
// 	{
// 		dup2(fd[2], STDIN_FILENO);
// 		dup2(fd[1], STDOUT_FILENO);
// 	}
// 	ft_close_all(fd);
// 	if (!chunk->args)
// 	{
// 		redir(chunk);
// 		close(data->stdin);
// 		close(data->stdout);
// 		free_data_exec(data);
// 		rl_clear_history();
// 		exit(0);
// 	}
// 	else if (is_builtin(chunk->cmd))
// 	{
// 		redir(chunk);
// 		do_builtin(data, chunk, chunk->cmd);
// 		redir(chunk);
// 		close(data->stdin);
// 		close(data->stdout);
// 		free_data_exec(data);
// 		rl_clear_history();
// 		exit(0);
// 	}
// 	if (is_dot(data->chunk->cmd))
// 		return (free_data_exec(data));
// 	if (is_dir(data->chunk->cmd))
// 		return (free_data_exec(data));
// 	redir(chunk);
// 	exec_cmd(data, chunk->args, data->envcpy);
// }

void	execs(t_data *data, t_chunk **chunk_lst)
{
	int		fd[3];
	t_chunk	*chunk;

	chunk = (*chunk_lst);
	data->stdin = dup(STDIN_FILENO);
	data->stdout = dup(STDOUT_FILENO);
	fd[2] = dup(STDIN_FILENO);
	while (chunk)
	{
		if (pipe(fd) != 0)
			err_pipe();
		chunk->pid = fork();
		if (chunk->pid == -1)
			err_fork();
		if (!chunk->pid)
			processs(data, chunk, fd);
		swap_pipes(fd);
		close(data->stdin);
		close(data->stdout);
		chunk = chunk->next;
	}
	close(fd[2]);
	waitit(data);
}

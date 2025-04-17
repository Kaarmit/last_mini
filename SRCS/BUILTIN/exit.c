/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:15:40 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/17 12:37:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	no_numeric(t_data *data, t_chunk *chunk)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(chunk->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	single_exit_s(255, UPDATE);
	free_data_exec(data);
	exit(255);
}

void	handle_exit_arg(t_data *data, t_chunk *chunk)
{
	int	code;

	code = ft_atoi(chunk->args[1]);
	if (ft_strcmp(chunk->args[1], "0") && !code)
		no_numeric(data, chunk);
	ft_putstr_fd("exit\n", 1);
	close(data->stdin);
	close(data->stdout);
	free_data_exec(data);
	single_exit_s(code, UPDATE);
	exit(code);
}

void	ft_exit(t_data *data)
{
	t_chunk	*chunk;
	int		code;

	chunk = data->chunk;
	if (!chunk->prev || !chunk->next)
		ft_putstr_fd("exit\n", 1);
	if (!chunk->args[1])
	{
		close(data->stdin);
		close(data->stdout);
		free_data_exec(data);
		code = single_exit_s(0, RETRIEVE);
		exit(code);
	}
	if (chunk->args[2])
	{
		single_exit_s(1, UPDATE);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	handle_exit_arg(data, chunk);
}

// void	ft_exit(t_data *data)
// {
// 	t_chunk	*chunk;
// 	int		code;

// 	chunk = data->chunk;
// 	if ((!chunk->prev && !chunk->next) || !chunk->prev || !chunk->next)
// 		ft_putstr_fd("exit\n", 1);
// 	if (!chunk->args[1])
// 	{
// 		close(data->stdin);
// 		close(data->stdout);
// 		free_data_exec(data);
// 		exit(single_exit_s(0, RETRIEVE));
// 	}
// 	if (chunk->args[2])
// 	{
// 		single_exit_s(1, UPDATE);
// 		ft_putstr_fd("exit: too many arguments\n", 2);
// 		return ;
// 	}
// 	code = ft_atoi(chunk->args[1]);
// 	if (ft_strcmp(chunk->args[1], "0") && !code)
// 		no_numeric(data, chunk);
// 	ft_putstr_fd("exit\n", 1);
// 	close(data->stdin);
// 	close(data->stdout);
// 	free_data_exec(data);
// 	single_exit_s(code, UPDATE);
// 	exit(code);
// }

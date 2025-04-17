/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:04:52 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/17 12:07:12 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "cd") == 0)
			return (1);
		else if (ft_strcmp(cmd, "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd, "env") == 0)
			return (1);
		else if (ft_strcmp(cmd, "echo") == 0)
			return (1);
		else if (ft_strcmp(cmd, "exit") == 0)
			return (1);
		else if (ft_strcmp(cmd, "unset") == 0)
			return (1);
		else if (ft_strcmp(cmd, "export") == 0)
			return (1);
		return (0);
	}
	return (0);
}

void	do_builtin_next(t_data *data, t_chunk *chunk, char *cmd)
{
	int	status;

	if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(data);
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		status = unset(chunk->args, &data->env, data);
		single_exit_s(status, UPDATE);
	}
	else if (ft_strcmp(cmd, "export") == 0)
	{
		status = export(&data->env, chunk->args, data);
		single_exit_s(status, UPDATE);
	}
}

void	do_builtin(t_data *data, t_chunk *chunk, char *cmd)
{
	int	status;

	if (ft_strcmp(cmd, "cd") == 0)
	{
		status = ft_cd(chunk, data);
		single_exit_s(status, UPDATE);
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		pwd(&data->env);
		single_exit_s(0, UPDATE);
	}
	else if (ft_strcmp(cmd, "env") == 0)
	{
		env(&data->env);
		single_exit_s(0, UPDATE);
	}
	else if (ft_strcmp(cmd, "echo") == 0)
	{
		echo(chunk);
		single_exit_s(0, UPDATE);
	}
	else
		do_builtin_next(data, chunk, cmd);
}

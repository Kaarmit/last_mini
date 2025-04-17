/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:00:13 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 14:20:33 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

static void	sig_child(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit\n", 1);
	else if (signal == SIGINT)
		write(1, "\n", 1);
}

void	set_sig_child(void)
{
	printf("1\n");
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	signal(SIGPIPE, sig_child);
}

void	heredoc_handler(int signal)
{
	(void)signal;
	g_sig_exit = 1;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	catch_sigint_exit(t_data *data)
{
	if (g_sig_exit)
	{
		g_sig_exit = 0;
		clean_program(data);
		exit(2);
	}
}

bool	end_cmd(int fd[2], int *pid)
{
	printf("4\n");
	waitpid(*pid, pid, 0);
	close(fd[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (single_exit_s(130, UPDATE), true);
	return (false);
}

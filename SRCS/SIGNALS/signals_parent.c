/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:13:46 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 15:39:21 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int		g_sig_exit = 0;

void	reset_prompt_handler(int signal)
{
	(void)signal;
	single_exit_s(130, UPDATE);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	g_sig_exit = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, reset_prompt_handler);
}

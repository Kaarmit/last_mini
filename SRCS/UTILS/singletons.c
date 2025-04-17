/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:37:37 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/13 10:37:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

t_env	*single_env(t_env *env, int mode)
{
	static t_env	*single_env = NULL;

	if (mode == UPDATE)
		single_env = env;
	else if (mode == RETRIEVE)
		return (single_env);
	return (single_env);
}

int	single_exit_s(int exit_s, int mode)
{
	static int	single_exit_s = 0;

	if (mode == UPDATE)
		single_exit_s = exit_s;
	if (mode == RETRIEVE)
		return (single_exit_s);
	return (single_exit_s);
}

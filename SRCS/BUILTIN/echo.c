/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:17 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 16:44:33 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	is_there_option(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (args[i][0] != '-' || args[i][1] != 'n')
			break ;
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		i++;
	}
	return (i);
}

void	echo(t_chunk *chunk)
{
	int	i;
	int	n;

	n = 0;
	i = is_there_option(chunk->args);
	if (i > 1)
		n = 1;
	while (chunk->args[i])
	{
		ft_putstr_fd(chunk->args[i], 1);
		if (chunk->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		printf("\n");
}

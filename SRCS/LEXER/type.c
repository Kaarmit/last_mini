/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:52:58 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 16:40:53 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	is_pipe(char *str)
{
	return (str[0] == '|');
}

int	is_heredoc(char *str)
{
	return (str[0] == '<' && str[1] == '<');
}

int	is_append(char *str)
{
	return (str[0] == '>' && str[1] == '>');
}

int	is_trunc(char *str)
{
	return (str[0] == '>');
}

int	is_input(char *str)
{
	return (str[0] == '<');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:39:04 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:41 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	count_existing_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	copy_existing_args(char **new_args, char **args, int old_size)
{
	int	i;

	i = 0;
	while (i < old_size)
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
			return (-1);
		i++;
	}
	return (0);
}

int	add_new_args(char ***new_args, t_token **token_lst, int *i)
{
	while (*token_lst && (*token_lst)->type == ARG)
	{
		(*new_args)[*i] = ft_strdup((*token_lst)->token);
		if (!(*new_args)[*i])
			return (-1);
		(*i)++;
		*token_lst = (*token_lst)->next;
	}
	return (0);
}

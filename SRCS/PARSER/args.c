/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:18:03 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/11 12:18:03 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	count_args(t_token *start)
{
	int	count;

	count = 0;
	while (start && start->type == ARG)
	{
		count++;
		start = start->next;
	}
	return (count);
}

char	**allocate_args(t_chunk *current_chunk, int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 2));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(current_chunk->cmd);
	if (!args[0])
		return (free(args), NULL);
	return (args);
}

int	fill_args(t_token **token_lst, t_chunk *current_chunk, int count)
{
	t_token	*start;
	int		i;

	start = *token_lst;
	i = 1;
	current_chunk->args = allocate_args(current_chunk, count);
	if (!current_chunk->args)
		return (-1);
	while (start && start->type < PIPE)
	{
		current_chunk->args[i] = ft_strdup(start->token);
		if (!current_chunk->args[i])
			return (malloc_free(current_chunk->args), -1);
		i++;
		start = start->next;
	}
	current_chunk->args[i] = NULL;
	(*token_lst) = start;
	return (0);
}

int	set_args(t_token **token_lst, t_chunk *current_chunk)
{
	int	count;

	count = count_args(*token_lst);
	return (fill_args(token_lst, current_chunk, count));
}

int	add_more_args(t_token **token_lst, t_chunk *current_chunk, int old_size)
{
	int		new_size;
	int		i;
	char	**new_args;

	i = 0;
	new_size = count_args(*token_lst);
	old_size = count_existing_args(current_chunk->args);
	new_args = malloc(sizeof(char *) * (old_size + new_size + 1));
	if (!new_args)
		return (-1);
	if (copy_existing_args(new_args, current_chunk->args, old_size) == -1)
	{
		free(new_args);
		return (-1);
	}
	if (add_new_args(&new_args, token_lst, &i) == -1)
	{
		free(new_args);
		return (-1);
	}
	new_args[i] = NULL;
	malloc_free(current_chunk->args);
	current_chunk->args = new_args;
	return (0);
}

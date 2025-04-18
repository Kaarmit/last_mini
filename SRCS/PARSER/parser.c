/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:50:23 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/10 17:50:23 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	argless_chunk(t_data *data)
{
	t_chunk	*start;

	if (!data || !data->chunk)
		return (-1);
	start = data->chunk;
	while (start)
	{
		if (start->cmd && !start->args)
		{
			start->args = malloc(sizeof(char *) * 3);
			if (!start->args)
				return (-1);
			start->args[0] = ft_strdup(start->cmd);
			if (!start->args[0])
			{
				free(start->args);
				return (-1);
			}
			start->args[1] = NULL;
		}
		start = start->next;
	}
	return (0);
}

int	new_chunk(t_data *data, t_token **token)
{
	t_chunk	*new_chunk;

	if (!token || !(*token))
		return (-1);
	if ((*token)->type == PIPE || !(*token)->prev)
	{
		new_chunk = lst_new_chunk();
		if (!new_chunk)
			return (-1);
		lst_add_back_chunk(&data->chunk, new_chunk);
		if ((*token)->next && (*token)->type == PIPE)
			(*token) = (*token)->next;
	}
	return (0);
}

void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

int	parse_tokens(t_data *data, t_token **tokens)
{
	t_token	*start;

	start = *tokens;
	while (start)
	{
		if (new_chunk(data, &start) == -1)
			return (1);
		if ((start->type == ARG && !start->prev) || (start->type == ARG
				&& start->prev && start->prev->type <= PIPE))
		{
			if (handle_word(&data->chunk, &start) == -1)
				return (1);
		}
		else if (start && start->type > PIPE)
		{
			if (handle_redirection(&data->chunk, &start, start->type) == -1)
				return (1);
		}
		else
			break ;
	}
	if (argless_chunk(data) == -1)
		return (1);
	free_lst(*tokens);
	return (0);
}

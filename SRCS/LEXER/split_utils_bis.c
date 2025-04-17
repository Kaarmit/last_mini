/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:57:02 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 16:35:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	remove_node(t_token **head, t_token *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (*head == node)
		*head = node->next;
	free(node->token);
	free(node);
}

static char	*merge_strs(char *s1, char *s2)
{
	char	*merged;

	merged = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!merged)
		return (NULL);
	ft_strcpy(merged, s1);
	ft_strcat(merged, s2);
	return (merged);
}

t_token	*merge_consecutive_args(t_token *curr, t_token **head)
{
	t_token	*next;
	t_token	*to_remove;
	char	*merged;

	next = curr->next;
	while (next && next->type < PIPE && next->type > ESPACE)
	{
		merged = merge_strs(curr->token, next->token);
		if (!merged)
			return (NULL);
		free(curr->token);
		curr->token = merged;
		to_remove = next;
		next = next->next;
		remove_node(head, to_remove);
	}
	return (curr->next);
}

t_token	*merge_args(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (curr->type < PIPE && curr->type > ESPACE)
			curr = merge_consecutive_args(curr, &head);
		else
			curr = curr->next;
	}
	return (head);
}

t_token	*remove_spaces(t_token *head)
{
	t_token	*curr;
	t_token	*next;

	curr = head;
	while (curr)
	{
		next = curr->next;
		if (curr->type == ESPACE)
			remove_node(&head, curr);
		curr = next;
	}
	return (head);
}

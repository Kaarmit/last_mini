/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:37:17 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 11:40:03 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	invalid_pipe(t_token *token)
{
	if (token->type > PIPE && token->next && token->next->type == PIPE
		&& token->next->next && token->next->next->type > PIPE)
		return (1);
	else if (token->type > PIPE && token->next && token->next->type > PIPE
		&& token->next->next && token->next->next->type == PIPE)
		return (1);
	else if (token->type == PIPE && token->next && token->next->type == PIPE)
		return (1);
	else if (token->type == PIPE && (!token->prev || !token->next))
		return (1);
	return (0);
}

int	unexpected_token(t_token *token)
{
	if (invalid_pipe(token))
		return (1);
	else if (token->type == INPUT && token->next && token->next->type == TRUNC
		&& !token->next->next)
		return (1);
	else if (token->type == HEREDOC && token->next
		&& token->next->type == INPUT)
		return (1);
	else if (token->type > PIPE && token->next && token->next->type > PIPE)
		return (1);
	return (0);
}

int	end_of_line(t_token *token)
{
	if (token->type == INPUT && token->next && token->next->type == TRUNC
		&& !token->next->next)
		return (1);
	else if (token->type == HEREDOC && token->next
		&& token->next->type == INPUT)
		return (1);
	else if (token->type > PIPE && !token->next)
		return (1);
	return (0);
}

int	separator(t_token *token)
{
	char	*value;

	if (unexpected_token(token))
	{
		if (token->type == PIPE && (!token->next || !token->prev))
			value = token->token;
		else if (token->type > PIPE && token->next && token->next->type > PIPE
			&& token->next->next && token->next->next->type == PIPE)
			value = token->next->next->token;
		else
			value = token->next->token;
		syntax_error(value);
		return (0);
	}
	else if (end_of_line(token))
	{
		syntax_error("newline");
		return (0);
	}
	return (1);
}

int	syntax_precheck(t_token **token)
{
	t_token	*temp;

	temp = (*token);
	while (temp)
	{
		if (!separator(temp))
			return (single_exit_s(2, UPDATE), 0);
		temp = temp->next;
	}
	if (temp && temp->token && ft_strcmp(temp->token, "./minishell") == 0)
		return (single_exit_s(2, UPDATE), 0);
	return (1);
}

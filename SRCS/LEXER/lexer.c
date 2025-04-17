/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:30:24 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/04/15 16:41:04 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	type(char *str)
{
	if (!str)
		return (ARG);
	if (is_pipe(str))
		return (PIPE);
	if (is_heredoc(str))
		return (HEREDOC);
	if (is_append(str))
		return (APPEND);
	if (is_trunc(str))
		return (TRUNC);
	if (is_input(str))
		return (INPUT);
	if (is_exp_arg(str))
		return (EXP_ARG);
	if (is_quoted_arg(str))
		return (ARG);
	if (is_space(str))
		return (ESPACE);
	return (ARG);
}

void	free_lst(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head->next;
		free(head->token);
		free(head);
		head = temp;
	}
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	add_end(t_token **head, t_token *new_node)
{
	t_token	*temp;

	if (!head || !new_node)
		return (1);
	if (!*head)
	{
		*head = new_node;
		new_node->next = NULL;
		new_node->prev = NULL;
		return (0);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
	new_node->next = NULL;
	return (0);
}

int	lexer(t_data *data)
{
	int	i;
	int	t;

	i = 0;
	data->token = NULL;
	data->tokens = ft_spliit(data->brut_input, ' ');
	if (!data->tokens)
		return (0);
	while (data->tokens[i])
	{
		t = type(data->tokens[i]);
		create_node(data, data->tokens[i], t, data->envcpy);
		i++;
	}
	data->token = merge_args(data->token);
	data->token = remove_spaces(data->token);
	if (!syntax_precheck(&data->token))
		return (0);
	malloc_free(data->tokens);
	return (1);
}

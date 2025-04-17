/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:36:26 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/04/15 15:07:44 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	create_node(t_data *data, char *token, int type, char **env)
{
	t_token	*node;

	if (!token)
		return ;
	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	node->token = ft_strdup(token);
	if (!node->token)
	{
		free(node);
		return ;
	}
	node->type = type;
	if (node->type == EXP_ARG)
		node->token = cut_dq(node->token);
	else
		node->token = expande_moi(node->token, env);
	(void)env;
	node->next = NULL;
	node->prev = NULL;
	add_end(&data->token, node);
	return ;
}

char	*cut_dq(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(str) - 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'')
			new[j++] = str[i];
		i++;
	}
	free(str);
	new[j] = '\0';
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truc_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:35:08 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 14:50:34 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	lst_add_back(t_env **lst, t_env *cmd)
{
	t_env	*start;

	if (!cmd)
		return ;
	if (*lst)
	{
		start = *lst;
		while (start->next)
			start = start->next;
		start->next = cmd;
		cmd->prev = start;
		return ;
	}
	else
		*lst = cmd;
}

t_env	*create_env_node(void)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->content = NULL;
	node->name = NULL;
	node->printable = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

char	*get_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	name = (char *)malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:06:01 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 17:06:27 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	count_env(t_env *envlst)
{
	int		count;
	t_env	*curr;

	count = 0;
	curr = envlst;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

char	*env_line(t_env *node)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(node->name, "=");
	if (!tmp)
		return (NULL);
	line = ft_strjoin(tmp, node->content);
	free(tmp);
	return (line);
}

char	**rewrite_env_tab(t_env *envlst)
{
	char	**new_env;
	t_env	*curr;
	int		len;
	int		i;

	len = count_env(envlst);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	curr = envlst;
	while (curr)
	{
		new_env[i] = env_line(curr);
		if (!new_env[i])
			return (NULL);
		i++;
		curr = curr->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

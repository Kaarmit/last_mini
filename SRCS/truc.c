/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:34:41 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 14:50:13 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*get_content(char *env)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	j = 0;
	while (env[i] != '=' && env[i])
		i++;
	while (env[j])
		j++;
	if (j != i)
	{
		i++;
		j = j - i;
		content = (char *)malloc((j + 1) * sizeof(char));
		if (!content)
			return (NULL);
		j = 0;
		while (env[i])
			content[j++] = env[i++];
		content[j] = '\0';
		return (content);
	}
	return (NULL);
}

int	fill_env_line(char *env, t_env **lst)
{
	t_env	*curr;
	char	*name;
	char	*content;

	curr = create_env_node();
	if (!curr)
		return (0);
	name = get_name(env);
	if (!name)
		return (0);
	content = get_content(env);
	if (content != NULL)
	{
		curr->content = ft_strdup(content);
		free(content);
		if (!(curr->content))
			return (free(name), 0);
		curr->printable = 1;
	}
	else
		curr->content = NULL;
	curr->name = ft_strdup(name);
	if (!(curr->name))
		return (free(curr->content), free(curr), 0);
	return (lst_add_back(lst, curr), free(name), 1);
}

void	print_env_lst(t_env **lst)
{
	t_env	*curr;

	curr = (*lst);
	while (curr)
	{
		printf("name: %s - content: %s\n", curr->name, curr->content);
		curr = curr->next;
	}
}

void	fill_env_lst(char **env, t_env **lst)
{
	int	i;

	i = 0;
	while (env[i])
	{
		fill_env_line(env[i], lst);
		i++;
	}
	//print_env_lst(lst);
	return ;
}

void	clear_env_lst(t_env **lst)
{
	t_env	*tmp;

	tmp = NULL;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free((*lst)->name);
		free(*lst);
		(*lst) = tmp;
	}
}

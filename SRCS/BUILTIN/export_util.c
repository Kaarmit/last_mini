/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:07:37 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 18:08:21 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	env_len(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_env	**copy_env_to_array(t_env **lst, int len)
{
	t_env	**array;
	t_env	*tmp;
	int		i;

	array = malloc(sizeof(t_env *) * len);
	if (!array)
		return (NULL);
	tmp = *lst;
	i = 0;
	while (tmp)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	return (array);
}

char	*get_var_name(char *var)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	if (var)
		while (var[i] && var[i] != '=')
			i++;
	else
		return (NULL);
	name = (char *)malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		name[i] = var[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_var_content(char *var)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (var[i])
		i++;
	while (var[j] && var[j] != '=')
		j++;
	name = ft_substr(var, j + 1, (i - j));
	if (!name)
		return (NULL);
	return (name);
}

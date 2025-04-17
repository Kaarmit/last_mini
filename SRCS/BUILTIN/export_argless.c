/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_argless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:56:59 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 17:37:54 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	swap_if_needed(t_env **array, int j)
{
	t_env	*tmp;

	if (ft_strcmp(array[j]->name, array[j + 1]->name) > 0)
	{
		tmp = array[j];
		array[j] = array[j + 1];
		array[j + 1] = tmp;
	}
}

void	bubble_sort_env(t_env **array, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			swap_if_needed(array, j);
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_env **sorted, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(sorted[i]->name, 1);
		if (sorted[i]->content)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(sorted[i]->content, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		i++;
	}
}

t_env	**sort_env(t_env **lst, int len)
{
	t_env	**array;

	array = copy_env_to_array(lst, len);
	if (!array)
		return (NULL);
	bubble_sort_env(array, len);
	return (array);
}

void	argless_export(t_env **lst)
{
	t_env	**sorted;
	int		len;

	len = env_len(*lst);
	sorted = sort_env(lst, len);
	if (!sorted)
		return ;
	print_sorted_env(sorted, len);
	free(sorted);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:55:23 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/18 11:02:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	**malloc_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

void	free_envcpy(char **envcpy)
{
	int	i;

	i = 0;
	while (envcpy[i])
	{
		free(envcpy[i]);
		i++;
	}
	free(envcpy);
}

void	clean_program(t_data *data)
{
	close(data->stdin);
	close(data->stdout);
	if (data->envcpy)
		free_envcpy(data->envcpy);
	clear_env_lst(&data->env);
	lst_clear_chunk(&data->chunk, &free_ptr);
	free(data);
	rl_clear_history();
	exit(0);
}

void	clean_program_exec(t_data *data)
{
	if (data->envcpy)
		free_envcpy(data->envcpy);
	clear_env_lst(&data->env);
	lst_clear_chunk(&data->chunk, &free_ptr);
	free(data);
	rl_clear_history();
	exit(127);
}

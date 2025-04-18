/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:42:22 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/18 11:02:52 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	free_data_exit(t_data *data)
{
	if (!data)
		exit(EXIT_SUCCESS);
	if (data->brut_input)
		free(data->brut_input);
	if (data->envcpy)
		free_envcpy(data->envcpy);
	if (data->chunk)
		lst_clear_chunk(&data->chunk, &free_ptr);
	if (data->env)
		clear_env_lst(&data->env);
	close(data->stdin);
	close(data->stdout);
	free(data);
}

void	free_data_bis(t_data *data)
{
	if (!data)
	{
		printf("data is NULL\n");
		close(data->stdin);
		close(data->stdout);
		exit(EXIT_SUCCESS);
	}
	if (data->tokens)
		malloc_free(data->tokens);
	if (data->token)
		free_lst(data->token);
	if (data->brut_input)
		free(data->brut_input);
	if (data->chunk)
		lst_clear_chunk(&data->chunk, &free_ptr);
}

void	free_data_exec(t_data *data)
{
	if (!data)
	{
		printf("data is NULL\n");
		exit(EXIT_SUCCESS);
	}
	if (data->chunk)
		lst_clear_chunk(&data->chunk, &free_ptr);
	free_envcpy(data->envcpy);
	clear_env_lst(&data->env);
	free(data);
}

void	free_data(t_data *data)
{
	if (!data)
		exit(EXIT_SUCCESS);
	if (data->tokens)
		malloc_free(data->tokens);
	if (data->token)
		free_lst(data->token);
	if (data->brut_input)
		free(data->brut_input);
	if (data->envcpy)
		free_envcpy(data->envcpy);
	if (data->chunk)
		lst_clear_chunk(&data->chunk, &free_ptr);
	if (data->env)
		clear_env_lst(&data->env);
	close(data->stdin);
	close(data->stdout);
	free(data);
	exit(EXIT_SUCCESS);
}

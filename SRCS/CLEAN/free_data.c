/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:42:22 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/15 22:04:00 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../INCLUDES/minishell.h"

// void	free_data_bis(t_data *data)
// {
// 	if (!data)
// 	{
// 		printf("data is NULL\n");
// 		close(data->stdin);
// 		close(data->stdout);
// 		exit(EXIT_SUCCESS);
// 	}
// 	if (data->tokens)
// 		malloc_free(data->tokens);
// 	if (data->token)
// 		free_lst(data->token);
// 	if (data->brut_input)
// 		free(data->brut_input);
// 	if (data->chunk)
// 		lst_clear_chunk(&data->chunk, &free_ptr);
// 	close(data->stdin);
// 	close(data->stdout);
// }

// void	free_data_exec(t_data *data)
// {
// 	if (!data)
// 	{
// 		printf("data is NULL\n");
// 		close(data->stdin);
// 		close(data->stdout);
// 		exit(EXIT_SUCCESS);
// 	}
// 	if (data->brut_input)
// 		free(data->brut_input);
// 	if (data->chunk)
// 		lst_clear_chunk(&data->chunk, &free_ptr);
// }

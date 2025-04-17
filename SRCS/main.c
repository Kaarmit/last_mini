/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:35:27 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/04/17 16:02:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*prompt(void)
{
	return (readline("minishell $> "));
}

void	eofl(t_data *data)
{
	if (data->brut_input)
		free(data->brut_input);
	lst_clear_chunk(&data->chunk, &free_ptr);
}

void	print_tokens(t_chunk *head)
{
	int			i;
	t_io_chunk	*io_handle;

	i = 0;
	printf("Liste chaînée chunk :\n");
	while (head)
	{
		io_handle = head->io_handle;
		printf("cmd: '%s', ", head->cmd);
		while (head->args && head->args[i])
		{
			printf("args[%d]: '%s' -", i, head->args[i]);
			i++;
		}
		while (io_handle)
		{
			printf("io_type: %d, io_path: %s -", io_handle->type,
				io_handle->path);
			io_handle = io_handle->next;
		}
		i = 0;
		printf("\n");
		head = head->next;
	}
	printf("Fin de la liste.\n");
}

void	programm(t_data *data)
{
	data->brut_input = prompt();
	while (1)
	{
		if (!data->brut_input)
		{
			//free(data->brut_input);
			free_envcpy(data->envcpy);
			lst_clear_chunk(&data->chunk, &free_ptr);
			clear_env_lst(&data->env);
			free(data);
			exit(EXIT_SUCCESS);
		}
		if (data->brut_input)
			add_history(data->brut_input);
		if (!lexer(data))
			free_data_bis(data);
		else
		{
			parse_tokens(data, &data->token);
			print_tokens(data->chunk);
			if (!data->chunk)
				free_data_bis(data);
			else
				pre_exec(data);
			eofl(data);
			set_signals();
			
		}
		data->brut_input = prompt();
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->chunk = NULL;
	data->env = NULL;
	// data->stdin = dup(0);
	// data->stdout = dup(1);
	data->envcpy = cpenv(envp);
	set_signals();
	fill_env_lst(data->envcpy, &data->env);
	programm(data);
	// free_envcpy(data->envcpy);
	(void)ac;
	(void)av;
}

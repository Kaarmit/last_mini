/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:30:48 by aarmitan          #+#    #+#             */
/*   Updated: 2025/02/26 12:31:48 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

t_chunk	*lst_new_chunk(void)
{
	t_chunk	*node;

	node = (t_chunk *)malloc(sizeof(t_chunk));
	if (node == NULL)
		return (NULL);
	node->io_handle = NULL;
	node->cmd = NULL;
	node->args = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	lst_add_back_chunk(t_chunk **lst, t_chunk *cmd)
{
	t_chunk	*start;

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

t_chunk	*lst_last_chunk(t_chunk *cmd)
{
	if (cmd == 0)
		return (0);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	lst_del_one_chunk(t_chunk *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (lst->cmd)
		(*del)(lst->cmd);
	if (lst->args)
		free_args(lst->args);
	if (lst->io_handle)
		lstclear_io_list(&lst->io_handle, del);
	free(lst);
}

void	lst_clear_chunk(t_chunk **lst, void (*del)(void *))
{
	t_chunk	*temp;

	temp = NULL;
	while (*lst)
	{
		temp = (*lst)->next;
		lst_del_one_chunk(*lst, del);
		*lst = temp;
	}
}

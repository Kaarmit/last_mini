/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:35 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 13:16:08 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	check_syntax_first_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	check_syntax(char *str)
{
	int	i;

	if (!str || !check_syntax_first_char(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	unset_it(char *var, t_env **lst)
{
	t_env	*curr;

	curr = (*lst);
	while (curr)
	{
		if (ft_strcmp(curr->name, var) == 0)
		{
			if (curr->prev)
				curr->prev->next = curr->next;
			else
				*lst = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			free(curr->name);
			free(curr->content);
			free(curr);
			return ;
		}
		curr = curr->next;
	}
}

static int	handle_unset_arg(char *arg, t_env **lst)
{
	if (!check_syntax(arg))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	unset_it(arg, lst);
	return (0);
}

int	unset(char **args, t_env **lst, t_data *data)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!args[i])
		return (0);
	while (args[i])
	{
		if (handle_unset_arg(args[i++], lst))
			ret = 1;
	}
	free_envcpy(data->envcpy);
	data->envcpy = rewrite_env_tab(data->env);
	if (!data->envcpy)
	{
		ft_putstr_fd("minishell: unset: malloc error\n", 2);
		free_data(data);
		single_exit_s(1, UPDATE);
		exit(1);
	}
	return (ret);
}

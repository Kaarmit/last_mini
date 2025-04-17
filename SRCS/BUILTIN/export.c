/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:30 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 13:16:42 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	change_content(t_env **lst, char *var)
{
	char	*name;
	char	*cont;
	t_env	*curr;

	curr = (*lst);
	name = get_var_name(var);
	if (!name)
		return (0);
	cont = get_var_content(var);
	if (!cont)
		return (0);
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			free(curr->content);
			curr->content = ft_strdup(cont);
			if (!curr->content)
				return (free(name), free(cont), 0);
			curr->printable = 1;
			return (free(name), free(cont), 0);
		}
		curr = curr->next;
	}
	return (free(name), free(cont), 0);
}

int	do_exist(t_env **lst, char *var)
{
	t_env	*curr;
	char	*name;

	if (!var)
		return (-1);
	name = get_var_name(var);
	if (!name)
		return (-1);
	curr = (*lst);
	while (curr)
	{
		if (ft_strcmp(name, curr->name) == 0)
			return (free(name), 1);
		curr = curr->next;
	}
	return (free(name), 0);
}

int	create_var(char *env, t_env **lst)
{
	t_env	*curr;
	char	*name;
	char	*content;

	curr = create_env_node();
	if (!curr)
		return (0);
	name = get_var_name(env);
	if (!name)
		return (0);
	content = get_var_content(env);
	if (content != NULL)
	{
		curr->content = ft_strdup(content);
		free(content);
		if (!(curr->content))
			return (free(name), 0);
	}
	curr->printable = 1;
	curr->name = ft_strdup(name);
	if (!(curr->name))
		return (free(curr->content), free(curr), 0);
	return (lst_add_back(lst, curr), free(name), 1);
}

static int	handle_export_arg(t_env **lst, char *arg)
{
	if (!check_syntax(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (do_exist(lst, arg))
	{
		if (change_content(lst, arg) == -1)
			return (1);
	}
	else
	{
		if (create_var(arg, lst) == 0)
			return (1);
	}
	return (0);
}

int	export(t_env **lst, char **args, t_data *data)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!args[1])
		return (argless_export(lst), 0);
	while (args[i])
	{
		if (handle_export_arg(lst, args[i]) != 0)
			ret = 1;
		i++;
	}
	free_envcpy(data->envcpy);
	data->envcpy = rewrite_env_tab(data->env);
	if (!data->envcpy)
	{
		ft_putstr_fd("minishell: export: malloc error\n", 2);
		free_data(data);
		single_exit_s(1, UPDATE);
		exit(1);
	}
	return (ret);
}


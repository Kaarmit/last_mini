/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:52:25 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 13:15:51 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*only_print_var(char *name, t_env **lst)
{
	t_env	*curr;

	curr = (*lst);
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0 && curr->printable)
			return (curr->content);
		curr = curr->next;
	}
	return (NULL);
}

void	replace_var(char *prev, char *new, t_env **lst)
{
	t_env	*curr;

	curr = (*lst);
	while (curr)
	{
		if (!ft_strcmp(prev, curr->name))
		{
			free(curr->content);
			curr->content = ft_strdup(new);
			return ;
		}
		curr = curr->next;
	}
	return ;
}

void	update_envcp(char **envcp, char *line, t_env *curr)
{
	int	i;

	i = 0;
	while (envcp[i])
	{
		if (ft_strncmp(envcp[i], "OLDPWD=", 7) == 0)
		{
			free(envcp[i]);
			envcp[i] = ft_strjoin(curr->name, line);
			return ;
		}
		i++;
	}
}

void	change_oldpwd(t_env **lst, char **envcp, char *cwd)
{
	t_env	*curr;
	char	*line;

	line = NULL;
	if (cwd)
		line = ft_strjoin("=", cwd);
	curr = *lst;
	while (curr)
	{
		if (ft_strcmp(curr->name, "OLDPWD") == 0)
		{
			free(curr->content);
			if (cwd)
				curr->content = ft_strdup(cwd);
			break ;
		}
		curr = curr->next;
	}
	update_envcp(envcp, line, curr);
	if (line)
		free(line);
}

void	change_pwd(t_env **lst, char *path)
{
	char	*cwd;
	char	*old_pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(path));
	old_pwd = only_print_var("PWD", lst);
	if (old_pwd)
	{
		free(path);
		replace_var("OLDPWD", old_pwd, lst);
		replace_var("PWD", cwd, lst);
		return (free(cwd));
	}
	else
	{
		free(old_pwd);
		free(cwd);
		replace_var("OLDPWD", path, lst);
		free(path);
	}
	return ;
}

// void	change_oldpwd(t_env **lst, char **envcp, char *cwd)
// {
// 	int		i;
// 	t_env	*curr;
// 	char	*line;

// 	i = 0;
// 	curr = (*lst);
// 	line = NULL;
// 	if (cwd)
// 		line = ft_strjoin("=", cwd);
// 	while (curr)
// 	{
// 		if (ft_strcmp(curr->name, "OLDPWD") == 0)
// 		{
// 			free(curr->content);
// 			if (cwd)
// 				curr->content = ft_strdup(cwd);
// 			break ;
// 		}
// 		curr = curr->next;
// 	}
// 	while (envcp[i])
// 	{
// 		if (ft_strncmp(envcp[i], "OLDPWD=", 7) == 0)
// 		{
// 			free(envcp[i]);
// 			envcp[i] = ft_strjoin(curr->name, line);
// 			if (!envcp[i])
// 				return ;
// 		}
// 	}
// 	if (line)
// 		free(line);
// }
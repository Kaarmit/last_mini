/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:10 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 13:08:48 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	cd_home(t_data *data)
{
	char	*path;
	char	*old_pwd;

	old_pwd = NULL;
	path = only_print_var("HOME", &data->env);
	if (!path)
	{
		perror("cd: ");
		// printf("%s: ", path);
		// perror("No such file or directory\n");
		return (1);
	}
	if (chdir(path) == 0)
	{
		old_pwd = only_print_var("PWD", &data->env);
		if (old_pwd)
		{
			replace_var("OLDPWD", old_pwd, &data->env);
			return (replace_var("PWD", path, &data->env), 0);
		}
		replace_var("OLD_PWD", ft_strdup(""), &data->env);
	}
	return (1);
}

int	cd_error(char *arg, char *cwd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free(cwd);
	return (1);
}

int	ft_cd(t_chunk *chunk, t_data *data)
{
	int		i;
	char	*cwd;

	i = 0;
	while (chunk->args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!chunk->args[1] || ft_strcmp(chunk->args[1], "~") == 0)
		return (cd_home(data));
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("chdir: error retrieving current directory: ", 2);
		return (1);
	}
	if (chdir(chunk->args[1]) != 0)
		return (cd_error(chunk->args[1], cwd));
	change_pwd(&data->env, cwd);
	free(cwd);
	return (0);
}

// int	ft_cd(t_chunk *chunk, t_data *data)
// {
// 	int		i;
// 	char	*cwd;

// 	i = 0;
// 	while (chunk->args[i])
// 		i++;
// 	if (i > 2)
// 	{
// 		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
// 		return (1);
// 	}
// 	if (!(chunk->args[1]) || strcmp(chunk->args[1], "~") == 0)
// 		return (cd_home(data));
// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		ft_putstr_fd("chdir: error retrieving current directory: ", 2);
// 		return (1);
// 	}
// 	if (chdir(chunk->args[1]) != 0)
// 	{
// 		ft_putstr_fd("minishell: cd: ", 2);
// 		ft_putstr_fd(chunk->args[1], 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 		return(free(cwd), 1) ;
// 	}
// 	return (change_pwd(&data->env, cwd), 0);
// }

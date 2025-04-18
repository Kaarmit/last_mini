/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:36:50 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/17 19:31:57 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	err_pipe(void)
{
	write(2, "pipe failed\n", 12);
	exit(127);
}

void	err_fork(void)
{
	write(2, "fork failed\n", 12);
	exit(127);
}

char	*find_path(char *cmd, t_data *data)
{
	int		i;
	char	*env_path;
	char	*part_path;
	char	**paths;
	char	*path;

	i = 0;
	env_path = only_print_var("PATH", &data->env);
	if (!env_path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	part_path = ft_strdup(env_path); // 🛠️ on fait une copie pour pouvoir la free
	if (!part_path)
		return (NULL);
	paths = ft_split(part_path, ':');
	free(part_path); // ✅ on libère uniquement la copie
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		char *tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}


void	exec_cmd(t_data *data, char **cmd, char **env)
{
	char	*path;

	if (!cmd || !cmd[0])
		return ;
	path = find_path(cmd[0], data);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		clean_program_exec(data);
	}
	if (execve(path, cmd, env) == -1)
		exit(127);
}
/*A TESTER*/
// static char	*check_paths(char **paths, char *cmd)
// {
// 	int		i;
// 	char	*part_path;
// 	char	*full_path;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		part_path = ft_strjoin(paths[i], "/");
// 		full_path = ft_strjoin(part_path, cmd);
// 		free(part_path);
// 		if (access(full_path, X_OK) == 0)
// 			return (full_path);
// 		free(full_path);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*find_path(char *cmd, char **env)
// {
// 	int		i;
// 	char	**paths;
// 	char	*path;

// 	i = 0;
// 	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
// 		i++;
// 	if (!env[i])
// 		return (NULL);
// 	if (ft_strchr(cmd, '/'))
// 	{
// 		if (access(cmd, X_OK) == 0)
// 			return (ft_strdup(cmd));
// 		return (NULL);
// 	}
// 	paths = ft_split(env[i] + 5, ':');
// 	path = check_paths(paths, cmd);
// 	i = -1;
// 	while (paths[++i])
// 		free(paths[i]);
// 	free(paths);
// 	return (path);
// }

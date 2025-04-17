#include "../INCLUDES/minishell.h"

int	is_dir(char *cmd)
{
	DIR		*dir;

	if (!cmd)
		return (0);
	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	closedir(dir);
	return (0);
}

int	is_dot(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": filename argument required\n", 2);
		return (1);
	}
	return (0);
}

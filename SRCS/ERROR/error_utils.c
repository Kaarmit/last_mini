/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:21:34 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/10 17:06:49 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*two_first_char(char *cmd)
{
	char	*opt;

	opt = malloc(sizeof(char) * 3);
	opt[0] = cmd[0];
	opt[1] = cmd[1];
	opt[2] = '\0';
	return (opt);
}

void	cd_pwd_error_chdir_getcwd(int builtin)
{
	if (builtin == 1)
		ft_putstr_fd("chdir: error retrieving current directory: ",
			STDERR_FILENO);
	else
		ft_putstr_fd("pwd: error retrieving current directory: ",
			STDERR_FILENO);
	ft_putstr_fd("getcwd: cannot access parent directories: ", STDERR_FILENO);
	ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
}

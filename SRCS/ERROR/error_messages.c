/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:58 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/10 17:06:34 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	error_control(int error, char *str)
{
	char	*mess;
	char	*err_mess;
	char	*complete_mess;

	err_mess = NULL;
	mess = ft_strdup("minishell: ");
	if (error == ARGS)
		err_mess = ft_strjoin(str, ": too many arguments\n");
	else if (error == EXPORT || error == EXPORT_OPT || error == UNSET
		|| error == UNSET_OPT || error == EXIT_NB)
		err_mess = error_message(error, str);
	else if (error == PATH)
		err_mess = ft_strjoin(str, ": HOME not set\n");
	else if (error == NOCMD)
		err_mess = ft_strjoin(str, ": Commnd not found\n");
	else if (error == PERM_DENIED)
		err_mess = ft_strjoin(str, ": Permission denied\n");
	else if (error == UNCLEAR_REDIR)
		err_mess = ft_strjoin(str, ": Ambiguous redirect\n");
	complete_mess = ft_strjoin(mess, err_mess);
	ft_putstr_fd(complete_mess, STDERR_FILENO);
	(free(mess), free(err_mess), free(complete_mess));
}

char	*error_message(int error, char *cmd)
{
	char	*temp;
	char	*res;
	char	*opt;

	temp = NULL;
	res = NULL;
	opt = two_first_char(cmd);
	if (error == EXPORT || error == UNSET || error == EXPORT_OPT
		|| error == UNSET_OPT)
	{
		if (error == EXPORT || error == UNSET)
			temp = ft_strjoin(cmd, "\' : not a valid identifier");
		else if (error == EXPORT_OPT || error == UNSET_OPT)
			temp = ft_strjoin(opt, "\': invalid option\n");
		if (error == EXPORT || error == UNSET_OPT)
			res = ft_strjoin("export: `", temp);
		else if (error == UNSET || error == UNSET_OPT)
			res = ft_strjoin("unset : `", temp);
	}
	else if (error == EXIT_NB)
	{
		temp = ft_strjoin(cmd, ": numeric argument required\n");
		res = ft_strjoin("exit:", temp);
	}
	return (free(temp), free(opt), res);
}

void	syntax_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token", STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	quote_error(char c)
{
	ft_putstr_fd("minishell : unexpected EOF while looking for matching `",
		STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putstr_fd("`\n", STDERR_FILENO);
}

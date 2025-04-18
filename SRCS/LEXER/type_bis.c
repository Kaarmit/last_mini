/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:53:36 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/17 21:02:27 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	is_exp_arg(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (str[0] == '\'' && str[len - 1] == '\'');
}

int	is_quoted_arg(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (str[0] == '"' && str[len - 1] == '"');
}

int	is_space(char *str)
{
	int	i = 0;

	if (!str || str[0] == '\0')
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	return (str[i] == '\0');
}


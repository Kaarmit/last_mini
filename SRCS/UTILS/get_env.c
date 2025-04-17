/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:36:52 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/04/17 12:11:02 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

// char	*ft_strdup(const char *s)
// {
// 	char	*copy;
// 	size_t	len;
// 	size_t	i;

// 	len = 0;
// 	while (s[len])
// 		len++;
// 	copy = (char *)malloc((len + 1) * sizeof(char));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		copy[i] = s[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }

int	count_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**cpenv(char **env)
{
	int		i;
	int		size;
	char	**envcpy;

	size = count_tab(env);
	envcpy = (char **)malloc((size + 1) * sizeof(char *));
	if (!envcpy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		envcpy[i] = ft_strdup(env[i]);
		if (!envcpy[i])
		{
			while (i > 0)
				free(envcpy[--i]);
			free(envcpy);
			return (NULL);
		}
		i++;
	}
	envcpy[i] = NULL;
	return (envcpy);
}

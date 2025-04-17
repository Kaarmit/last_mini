/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:07:20 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/13 12:22:09 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*str_before(char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '$')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*str_after(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 1;
	while (s[i] && s[i] != '$' && s[i] != ' ')
		i++;
	j = i;
	while (s[i])
		i++;
	str = malloc((i - j + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[j])
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*cplc2(char *s)
{
	char	*str;
	int		i;

	i = 1;
	while (s[i] && s[i] != ' ' && s[i] != '$')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 1;
	while (s[i] && s[i] != ' ' && s[i] != '$')
	{
		str[i - 1] = s[i];
		i++;
	}
	str[i - 1] = '=';
	str[i] = '\0';
	return (str);
}

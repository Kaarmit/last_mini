/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:26:45 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/04/15 15:05:56 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	quote_handle(char *s, char quote, int i)
{
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (!s[i])
		ft_putstr_fd("unclosed quote\n", 2);
	i++;
	return (i);
}

char	*create_word(char *start, int len)
{
	char	*word;

	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}

char	*is_double_quote(char **s, char quote)
{
	char	*start;

	if (quote == '\'')
	{
		start = *s;
		(*s)++;
	}
	else
	{
		(*s)++;
		start = *s;
	}
	return (start);
}

int	dq_len(char **s, char *start, char quote)
{
	if (quote == '\'')
		return ((*s - start) + 1);
	return (*s - start);
}

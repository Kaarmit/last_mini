/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:42:10 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/04/15 16:02:18 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	skip_word(char *s, int i, char c)
{
	while (s[i] && s[i] != c && s[i] != '"' && s[i] != '\'' && s[i] != '|'
		&& s[i] != '<' && s[i] != '>')
		i++;
	return (i);
}

int	count_words(char *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i);
		else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			i = skip_operator(s, i);
		else
			i = skip_word(s, i, c);
		count++;
	}
	return (count);
}

char	**insert_words(char *s, char c, int count)
{
	char	**words;
	int		i;

	words = (char **)malloc((count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	while (i < count)
	{
		words[i] = malloc_word(&s, c);
		if (!words[i])
		{
			while (i > 0)
				free(words[--i]);
			free(words);
			return (NULL);
		}
		i++;
	}
	words[i] = NULL;
	return (words);
}

int	count(char *s, char c)
{
	int	i;

	i = 0;
	return (count_words(s, c, i));
}

char	**ft_spliit(char *s, char c)
{
	int		count;
	char	**split;

	if (!s)
		return (NULL);
	count = count_words(s, c, 0);
	split = insert_words(s, c, count);
	return (split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_third.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:42:44 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/16 17:02:15 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*malloc_quote_word(char **s)
{
	char	quote;
	char	*start;
	int		len;

	quote = **s;
	(*s)++;
	start = *s;
	while (**s && **s != quote)
		(*s)++;
	len = *s - start;
	if (**s == quote)
		(*s)++;
	if (len == 0)
		return (ft_strdup(""));
	return (create_word(start, len));
}


char	*malloc_operator_word(char **s)
{
	char	*start;
	int		len;

	start = *s;
	if ((*s)[1] == **s && **s != '|')
		(*s)++;
	(*s)++;
	len = *s - start;
	return (create_word(start, len));
}

int	skip_quotes(char *s, int i)
{
	char	quote;

	quote = s[i];
	return (quote_handle(s, quote, i));
}

int	skip_operator(char *s, int i)
{
	if (s[i + 1] == s[i] && s[i] != '|')
		i++;
	return (i + 1);
}

char	*malloc_word(char **s, char c)
{
	char	*start;

	if (**s == c)
	{
		start = *s;
		while (**s == c)
			(*s)++;
		return (create_word(start, 1));
	}
	if (**s == '"' || **s == '\'')
		return (malloc_quote_word(s));
	if (**s == '|' || **s == '<' || **s == '>')
		return (malloc_operator_word(s));
	start = *s;
	while (**s && **s != c && **s != '"' && **s != '\'' && **s != '|'
		&& **s != '<' && **s != '>')
		(*s)++;
	return (create_word(start, *s - start));
}

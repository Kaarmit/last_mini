/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:40:03 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/17 13:31:28 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

char	*ft_strdup(const char *s)
{
	size_t	src_len;
	char	*s2;

	src_len = ft_strlen(s);
	s2 = malloc(sizeof(char) * (src_len + 1));
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s, src_len);
	s2[src_len] = '\0';
	return (s2);
}

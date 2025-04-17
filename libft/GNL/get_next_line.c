/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:55:56 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/17 13:29:48 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

void	test(void)
{
	get_next_line(-42);
}

char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ftt_strdup("");
		temp = stash;
		stash = ftt_strjoin(temp, buffer);
		free(temp);
		if (ftt_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*set_line(char *line_buffer)
{
	size_t	i;
	char	*stash;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i])
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	stash = ftt_substr(line_buffer, i + 1, ftt_strlen(line_buffer) - (i + 1));
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || read(fd, buffer, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		return (NULL);
	}
	line = fill_line_buffer(fd, stash, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	stash = set_line(line);
	return (line);
}

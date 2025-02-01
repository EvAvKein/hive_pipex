/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:26:47 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/29 11:28:36 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	move_to_start(char *s, size_t start_i)
{
	size_t	s_i;

	if (start_i == 0)
		return ;
	s_i = 0;
	while (s[start_i])
		s[s_i++] = s[start_i++];
	while (s_i < start_i)
		s[s_i++] = '\0';
}

static void	reset_buffer(char *buffer, ssize_t *buffer_nl_i)
{
	if (*buffer_nl_i >= 0)
		move_to_start(buffer, *buffer_nl_i + 1);
	else
		ft_bzero(buffer, BUFFER_SIZE);
}

static int	initialize_line(char **line, char *buffer, ssize_t *buffer_nl_i)
{
	if (*buffer)
	{
		*line = ft_strdup_until_nl(buffer, buffer_nl_i);
		if (!*line)
			return (0);
		reset_buffer(buffer, buffer_nl_i);
	}
	else
	{
		*line = malloc(sizeof(char));
		if (!*line)
			return (0);
		*line[0] = 0;
	}
	return (1);
}

static int	append_to_line(char **line, char *buffer, ssize_t *buffer_nl_i)
{
	size_t	total_len;
	char	*combined;
	size_t	combined_i;
	size_t	i;

	total_len = ft_strlen(*line) + ft_strlen_until_nl(buffer, buffer_nl_i);
	combined = malloc((total_len + 1) * sizeof(char));
	if (!combined)
	{
		free(*line);
		return (0);
	}
	combined_i = 0;
	i = 0;
	while ((*line)[i])
		combined[combined_i++] = (*line)[i++];
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		combined[combined_i++] = buffer[i++];
	if (buffer[i] == '\n')
		combined[combined_i++] = '\n';
	combined[combined_i] = '\0';
	free(*line);
	*line = combined;
	return (1);
}

char	*get_next_line(int fd)
{
	static char		buffers[FILES_CAPACITY][BUFFER_SIZE + 1];
	ssize_t			buffer_nl_i;
	char			*line;

	buffer_nl_i = -1;
	if (BUFFER_SIZE < 1 || FILES_CAPACITY < 1 || fd > FILES_CAPACITY - 1
		|| fd < 0 || !initialize_line(&line, buffers[fd], &buffer_nl_i))
		return (NULL);
	if (buffer_nl_i >= 0)
		return (line);
	while (1)
	{
		if (!buffers[fd][0] && read(fd, buffers[fd], BUFFER_SIZE) < 1)
		{
			if (line[0])
				return (line);
			free(line);
			return (NULL);
		}
		if (!append_to_line(&line, buffers[fd], &buffer_nl_i))
			return (NULL);
		reset_buffer(buffers[fd], &buffer_nl_i);
		if (buffer_nl_i >= 0)
			return (line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:08:27 by yoel-idr          #+#    #+#             */
/*   Updated: 2022/10/31 00:49:04 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*reading_fd(int fd, char *stash)
{
	char	*buffer;
	int		readed;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readed = 1;
	while (!ft_strchr(stash) && readed != 0)
	{
		readed = (int)read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[readed] = 0;
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = reading_fd(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_subline(stash[fd]);
	stash[fd] = cleaning_stash(stash[fd]);
	return (line);
}

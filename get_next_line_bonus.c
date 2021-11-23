/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 23:33:15 by alaajili          #+#    #+#             */
/*   Updated: 2021/11/21 00:43:03 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_join(int fd, char *save)
{
	char	*buff;
	int		i;

	i = 1;
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (check_next_line(save) == 0 && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			buff = NULL;
			return (NULL);
		}
		buff[i] = '\0';
		save = ft_strjoin(save, buff);
	}
	free (buff);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = get_join(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	if (!save[fd][0])
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	line = get_line(save[fd]);
	save[fd] = rest_of_line(save[fd]);
	return (line);
}

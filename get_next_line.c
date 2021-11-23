/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:46:35 by alaajili          #+#    #+#             */
/*   Updated: 2021/11/21 00:41:00 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_join(fd, save);
	if (!save)
		return (NULL);
	if (!save[0])
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	line = get_line(save);
	save = rest_of_line(save);
	return (line);
}

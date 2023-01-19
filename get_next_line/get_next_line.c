/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 18:14:27 by gmeoli            #+#    #+#             */
/*   Updated: 2023/01/19 18:24:22 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*file;
	static char	*save[4096];
	size_t		i;

	i = 0;
	if (fd < 0 || fd > 4096)
		return (NULL);
	save[fd] = get_lineg(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	while (save[fd][i] && save[fd][i] != '\n')
		i++;
	file = ft_substrg(save[fd], 0, i + 1);
	save[fd] = ft_saveg(save[fd], file);
	return (file);
}

char	*get_lineg(int fd, char *save)
{
	int		count;
	char	*buffer;

	count = 1;
	if (!save)
		save = ft_callocg (1, 1);
	while (count > 0 && ft_strchrg(save, '\n') == -1)
	{
		buffer = ft_callocg(1, BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		count = read(fd, buffer, BUFFER_SIZE);
		if (count < 0 || (count == 0 && save[0] == 0))
		{
			free(save);
			free(buffer);
			return (NULL);
		}
		save = ft_strjoing(save, buffer);
		free (buffer);
	}
	return (save);
}

char	*ft_saveg(char *save, char *file)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (file[i])
		i++;
	if (save[i] == 0)
	{
		free(save);
		return (NULL);
	}
	tmp = ft_substrg(save, i, ft_strleng(save) - i);
	free(save);
	save = ft_substrg(tmp, 0, ft_strleng(tmp));
	free(tmp);
	return (save);
}

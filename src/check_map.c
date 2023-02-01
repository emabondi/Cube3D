/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:13:03 by gmeoli            #+#    #+#             */
/*   Updated: 2023/02/01 20:43:39 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	check_map(t_map *map)
{
	(void)map;
	return (0);
}

void	ft_malloc_map(t_data *data, int fd)
{
	int		i;
	int		j;
	char	*buff;

	data->map.matrix = (char **) malloc(sizeof(char *) * data->map.height);
	i = 0;
	while (i < data->map.height)
	{
		data->map.matrix[i] = (char *) malloc(sizeof(char) * data->map.width);
		ft_bzero(data->map.matrix[i], data->map.width);
		i++;
	}
	i = -1;
	while (++i < data->map.height)
	{
		buff = get_next_line(fd);
		i++;
		j = 0;
		while (buff[j] != '\0' && buff[j] != '\n')
		{
			data->map.matrix[i][j] = buff[j];
			j++;
		}
		free(buff);
	}
	//i = -1;
	//while (++i < data->map.height)
	//{
	//	printf("%s\n", data->map.matrix[i]);
	//}
}

void	get_map(t_data *data, char *f, int lines)
{
	int		fd;
	char	*buff;
	int		i;

	fd = open(f, O_RDONLY);
	if (fd == -1)
		ft_error("No such file or directory");
	buff = get_next_line(fd);
	i = lines - data->map.height;
	while (--i > 1)
	{
		free (buff);
		buff = get_next_line(fd);
	}
	ft_malloc_map(data, fd);
	close(fd);
}

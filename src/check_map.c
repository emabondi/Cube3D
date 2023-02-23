/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:13:03 by gmeoli            #+#    #+#             */
/*   Updated: 2023/02/23 15:17:11 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	check_zero(char **matrix, int i, int j)
{
	if (matrix[(i) - 1][(j)] == 0 || matrix[(i) - 1][(j)] == ' '
		|| matrix[(i)][(j) - 1] == 0 || matrix[(i)][(j) - 1] == ' '
		|| matrix[(i) + 1][(j)] == 0 || matrix[(i) + 1][(j)] == ' '
		|| matrix[(i)][(j) + 1] == 0 || matrix[(i)][(j) + 1] == ' ')
		ft_error("Unclosed map");
}

void	check_map(t_data *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->matrix[i] != NULL)
	{
		j = 0;
		while (map->matrix[i][j] != '\0')
		{
			if (map->matrix[i][j] == '0' && (i == 0 || i == map->height - 1 \
				|| j == 0 || j == map->width - 1))
				ft_error("Border map error");
			else if (map->matrix[i][j] == '0' || map->matrix[i][j] == 'N'\
				|| map->matrix[i][j] == 'S' || map->matrix[i][j] == 'E' \
				|| map->matrix[i][j] == 'W')
				check_zero(map->matrix, i, j);
			j++;
		}
		i++;
	}
	if (map->pov == -1)
		ft_error("Missing player");
	//printf ("x:%f y:%f pov:%d", map->x, map->y, map->pov);
	write(1, "tutto ok\n", 9);
}

void	check_pov(t_data *map, char c, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (map->pov != -1)
			ft_error("Double player");
		else if (c == 'N')
			map->pov = 270;
		else if (c == 'E')
			map->pov = 1;
		else if (c == 'S')
			map->pov = 90;
		else if (c == 'W')
			map->pov = 180;
		map->x = j + 0.4;
		map->y = i ;
		map->matrix[i][j] = '0';
	}
}

void	ft_malloc_map(t_data *data, int fd)
{
	int		i;
	int		j;
	char	*buff;

	data->matrix = (char **) malloc(sizeof(char *) * data->height + 1);
	data->matrix[data->height] = NULL;
	i = -1;
	while (++i < data->height)
	{
		data->matrix[i] = (char *) malloc(sizeof(char) * data->width + 1);
		ft_memset(data->matrix[i], '\0', data->width + 1);
	}
	i = -1;
	while (++i < data->height)
	{
		buff = get_next_line(fd);
		j = 0;
		while (buff[j] != '\0' && buff[j] != '\n')
		{
			check_pov(data, buff[j], i, j);
			data->matrix[i][j] = buff[j];
			j++;
		}
		free(buff);
	}
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
	i = lines - data->height;
	while (--i > 1)
	{
		free (buff);
		buff = get_next_line(fd);
	}
	free(buff);
	ft_malloc_map(data, fd);
	close(fd);
}

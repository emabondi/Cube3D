/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:13:03 by gmeoli            #+#    #+#             */
/*   Updated: 2023/03/29 19:18:49 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	check_zero(char **matrix, int i, int j)
{
	if (matrix[(i) - 1][(j)] == 0 || matrix[(i) - 1][(j)] == ' ' \
		|| matrix[(i)][(j) - 1] == 0 || matrix[(i)][(j) - 1] == ' ' \
		|| matrix[(i) + 1][(j)] == 0 || matrix[(i) + 1][(j)] == ' ' \
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
				|| map->matrix[i][j] == 'W' || map->matrix[i][j] == 'd'\
				|| map->matrix[i][j] == 'D')
				check_zero(map->matrix, i, j);
			else if (map->matrix[i][j] != ' ' && map->matrix[i][j] != '1')
				ft_error("Unknown char in map");
			j++;
		}
		i++;
	}
	if (map->pov == -1)
		ft_error("Missing player");
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
		map->y = i;
		map->matrix[i][j] = '0';
	}
}

void	ft_malloc_map_2(t_data *data, int fd)
{
	int		i;
	char	*buff;
	int		o;
	int		j;

	i = -1;
	while (++i < data->height)
	{
		buff = get_next_line(fd);
		j = 0;
		o = 0;
		while (buff[j] != '\0' && buff[j] != '\n')
		{
			check_pov(data, buff[j], i, j);
			copy_char(data, buff[j], &o, &i);
			j++;
		}
		free(buff);
	}
}

void	ft_malloc_map(t_data *data, int fd)
{
	int		i;

	data->matrix = (char **) malloc(sizeof(char *) * data->height + 1);
	data->matrix[data->height] = NULL;
	i = -1;
	while (++i < data->height)
	{
		data->matrix[i] = (char *) malloc(sizeof(char) * data->width + 1);
		ft_memset(data->matrix[i], '\0', data->width + 1);
	}
	ft_malloc_map_2(data, fd);
}

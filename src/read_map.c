/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 21:51:14 by gmeoli            #+#    #+#             */
/*   Updated: 2023/01/19 17:59:11 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

char	**ft_fill_matrix(t_map *map, char *maps)
{
	int		i;
	int		j;
	char	**matrix;

	//map->height = ft_height(maps);
	//map->width = ft_width(maps);
	i = -1;
	matrix = malloc(sizeof(char *) * map->height + 1);
	while (++i < map->height)
	{
		matrix[i] = malloc(sizeof(char) * map->width + 1);
		j = -1;
		while (++j < map->width)
		{
			matrix[i][j] = maps[i];
		}
		matrix[i][j] = '\0';
	}
	matrix[i] = NULL;
	return (matrix);
}

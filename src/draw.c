/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/07 21:07:02 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	my_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_image *image, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			my_pixel_put(image, x * 10 + j + 10 , y * 10 + i + 10, 255);
	}
}

void	draw_circle(t_image *image, int x, int y)
{
	int	i;
	int	j;
	int	o;

	i = -1;
	o = 0;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			if ((j > 4 - o) && (j < 4 + o))
				my_pixel_put(image, x * 10 + j + 10 , y * 10 + i + 10, 200);
		}
		if (i < 4)
			o++;
		else
			o--;
	}
}

void	draw_minimap(t_map *map, t_image *image)
{
	int	i;
	int	j;

	i = -1;
	while (map->matrix[++i] != NULL)
	{
		j = -1;
		while (map->matrix[i][++j] != '\0')
		{
			if (map->matrix[i][j] == '1')
				draw_square(image, j, i);
			else if ((map->x - (float)j > 0) && (map->x - (float)j < 0.5) && (map->y - (float)i > 0) && (map->y - (float)i < 0.5))
				draw_circle(image, j, i);
				//my_pixel_put(image, j * 10 + 10 , i * 10 + 10, 200);
		}
	}
}

int	draw(t_data *data)
{
	//draw_game();
	draw_minimap(&data->map, data->minimap);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 0, 0);
	//sleep(3);
	//mlx_clear_window(data->mlx, data->win);
	return (0);
}

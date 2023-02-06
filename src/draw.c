/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/06 22:49:11 by ebondi           ###   ########.fr       */
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

void	draw_minimap(t_image *image, char **map)
{
	int i;
	int j;

	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == '1')
				draw_square(image, j, i);
		}
	}
}

int	draw(t_data *data)
{
	//draw_game();
	draw_minimap(data->minimap, data->map.matrix);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 0, 0);
	//sleep(3);
	//mlx_clear_window(data->mlx, data->win);
	return (0);
}

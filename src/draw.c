/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/15 16:49:48 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	my_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_image *image, int x, int y, int c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			my_pixel_put(image, x * 10 + j + 10 , y * 10 + i + 10, c);
	}
}

void	draw_circle(t_image *image, int x, int y)
{
	int	i;
	int	j;
	int	o;
	int tot;

	i = -1;
	o = 2;
	while (++i < 7)
	{
		j = 0;
		tot = 7 - (o * 2);
		while (j < o)
			j++;
		while (tot > 0)
		{
			my_pixel_put(image, x * 10 + j + 11, y * 10 + i + 11, 16449536);
			j++;
			tot--;
		}
		if (i < 2)
			o--;
		else if (i > 3)
			o++;
	}
}

void	draw_minimap(t_data *map, t_image *image)
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
				draw_square(image, j, i, 200);
			else if ((j > map->x - 0.5) && (j < map->x + 0.5) && (i > map->y - 0.5) && (i < map->y + 0.5))
				draw_circle(image, j, i);
			else
				draw_square(image, j, i, 0);
		}
	}
	//ft_putstr_fd("ESCO\n", 1);
}

int	draw(t_data *data)
{
	//draw_game();
	draw_minimap(data, data->minimap);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 0, 0);
	return (0);
}

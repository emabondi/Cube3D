/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/16 13:45:25 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	trace_ray(t_data *data, t_image *minimap, double rayAngle)
{
	double	ray_cos;
	double	ray_sin;
	char	wall;
	double	ray_x;
	double	ray_y;

	ray_cos = cos(rayAngle * PI / 180) / 256;
	ray_sin = sin(rayAngle * PI / 180) / 256;
	wall = '0';
	ray_x = data->x;
	ray_y = data->y;
	while (wall == '0')
	{
		my_pixel_put(minimap, (int)ray_x * 10 + 10, (int)ray_y * 10 + 10, 16774656);
		ray_x += ray_cos;
		ray_y += ray_sin;
		wall = data->matrix[(int)ray_y][(int)ray_x];
	}
	//trace_ray2();
}

void	raycasting(t_data *data, t_image *minimap)
{
	double	rayAngle;
	double	increment;
	int		i;

	rayAngle = data->pov - data->half_fov;
	increment = data->fov / data->w_width;
	i = 0;
	while (i < data->w_width)
	{
		trace_ray(data, minimap, rayAngle);
		rayAngle += increment;
		i++;
	}
}

void	draw_minimap(t_data *data, t_image *minimap)
{
	int	i;
	int	j;

	i = -1;
	while (data->matrix[++i] != NULL)
	{
		j = -1;
		while (data->matrix[i][++j] != '\0')
		{
			if (data->matrix[i][j] == '1')
				draw_square(minimap, j, i, 200);
			else if ((j > data->x - 0.5) && (j < data->x + 0.5) && (i > data->y - 0.5) && (i < data->y + 0.5))
				draw_circle(minimap, j, i);
			else
				draw_square(minimap, j, i, 0);
		}
	}
	raycasting(data, minimap);
}

int	draw(t_data *data)
{
	//draw_game();
	draw_minimap(data, data->minimap);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/06 22:47:11 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	trace_game_line(t_data *data, float dist, const int x)
{
	int	wall;
	int	y;

	wall = (int) data->half_w_height / dist;
	y = -1;
	while (++y < data->half_w_height - wall)
		my_pixel_put(data->game, x, y, data->ceiling);
	while (++y < data->half_w_height + wall)
		my_pixel_put(data->game, x, y, 16713222);
	while (++y < data->w_height)
		my_pixel_put(data->game, x, y, data->floor);
}

void	trace_ray(t_data *data, t_image *minimap, double rayAngle, const int x)
{
	double	ray_cos;
	double	ray_sin;
	double	ray_x;
	double	ray_y;
	float	dist;

	rayAngle *= 0.0174533;
	ray_cos = cos(rayAngle);
	ray_sin = sin(rayAngle);
	ray_x = data->x;
	ray_y = data->y;
	dist = 0.0;
	while (data->matrix[ (int)(ray_y + ray_sin * dist ) ][ (int)(ray_x + ray_cos * dist)] != '1')
	{
		my_pixel_put(minimap, (int) ((ray_x + ray_cos * dist) * data->r_width), (int) (( ray_y + ray_sin * dist) * data->r_height), 16774656);
		dist += 0.01;
	}
	//printf("%d)dist:%f\n", x, dist);
	trace_game_line(data, dist, x);
}

void	raycasting(t_data *data)
{
	double	rayAngle;
	double	increment;
	int		i;

	rayAngle = data->pov - data->half_fov;
	//increment = (PI / 180);
	increment = (double)data->fov / (double)data->w_width;
	//printf("ray:%f increment:%f\n", rayAngle, increment);
	i = 0;
	//while (i < data->w_width)
	while (rayAngle <= data->pov + data->half_fov)
	{
		//printf("ray:%f\n", rayAngle);
		trace_ray(data, data->minimap, rayAngle, i);
		rayAngle += increment;
		i++;
	}
}

void	draw_minimap(t_data *data)
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
				draw_square(data, j * data->r_width, i * data->r_height,200);
			else
				draw_square(data, j * data->r_width, i * data->r_height, 0);
		}
	}
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->game->img, 0, 0);
	draw_circle(data->minimap, data->x * data->r_width - 2.5, data->y * data->r_height - 2.5);
}

int	draw(t_data *data)
{
	draw_minimap(data);
	// draw_game();
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 10, 10);
	return (0);
}

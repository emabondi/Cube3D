/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/09 14:49:44 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	get_orientation(t_data *data, double x, double y)
{
	if (data->matrix[(int)(y - 0.005)][(int)x] == '1')
		return (1);
	else if (data->matrix[(int)(y + 0.005)][(int)x] == '1')
		return (2);
	else if (data->matrix[(int)y][(int)(x - 0.005)] == '1')
		return (3);
	else if (data->matrix[(int)y][(int)(x + 0.005)] == '1')
		return (4);
	else
		return (0);
}

void	trace_game_line(t_data *data, int orientation, float dist, const int x)
{
	int	wall;
	int	y;

	if (dist < 1)
		dist = 1;
	wall = (int) data->half_w_height / dist;
	y = -1;
	while (++y < data->half_w_height - wall)
		my_pixel_put(data->game, x, y, data->ceiling);
	if (orientation == 1)
		while (++y < data->half_w_height + wall)
			my_pixel_put(data->game, x, y, 3137239);
	else if (orientation == 2)
		while (++y < data->half_w_height + wall)
			my_pixel_put(data->game, x, y, 4723712);
	else if (orientation == 3)
		while (++y < data->half_w_height + wall)
			my_pixel_put(data->game, x, y, 15953948);
	else if (orientation == 4)
		while (++y < data->half_w_height + wall)
			my_pixel_put(data->game, x, y, 15330053);
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

	rayAngle *= (PI / 180.0);
	ray_cos = cos(rayAngle) / 256;
	ray_sin = sin(rayAngle) / 256;
	ray_x = data->x;
	ray_y = data->y;
	dist = 0.0;
	while (data->matrix[(int)ray_y][(int)ray_x] != '1')
	{
		ray_x += ray_cos;
		ray_y += ray_sin;
		my_pixel_put(minimap, (int)(ray_x * data->r_width), (int) (ray_y * data->r_height), 16774656);
	}
	dist = sqrt(powf(data->x - ray_x, 2) + powf(data->y - ray_y, 2));
	dist = dist * cos((rayAngle - (PI / 180.0) * data->pov));
	ray_x -= ray_cos;
	ray_y -= ray_sin;
	trace_game_line(data, get_orientation(data, ray_x, ray_y), dist, x);
}

void	raycasting(t_data *data)
{
	double	rayAngle;
	double	increment;
	int		i;

	rayAngle = data->pov - data->half_fov;
	increment = (double)data->fov / (double)data->w_width;
	i = 0;
	while (rayAngle <= data->pov + data->half_fov)
	{
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
	mlx_put_image_to_window(data->mlx, data->win, data->game->img, 0, 0);
	draw_circle(data->minimap, data->x * data->r_width - 2.5, data->y * data->r_height - 2.5);
}

int	draw(t_data *data)
{
	ft_movements(data);
	draw_minimap(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 10, 10);
	return (0);
}

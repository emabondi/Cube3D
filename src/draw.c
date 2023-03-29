/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/29 18:52:43 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	get_orientation(t_data *data, double x, double y, double rayAngle)
{
	if (data->matrix[(int)(y + 0.005)][(int)x] != '1' &&
		(data->matrix[(int)y][(int)(x - 0.005)] == '1'
			|| data->matrix[(int)y][(int)(x + 0.005)] == '1') && data->y > y)
		return (1);
	if (data->matrix[(int)(y - 0.005)][(int)x] != '1' &&
		(data->matrix[(int)y][(int)(x - 0.005)] == '1'
			|| data->matrix[(int)y][(int)(x + 0.005)] == '1') && data->y < y)
		return (2);
	if (data->matrix[(int)y][(int)(x + 0.005)] != '1' &&
		(data->matrix[(int)(y - 0.005)][(int)x] == '1'
			|| data->matrix[(int)(y + 0.005)][(int)x] == '1') && data->x > x)
		return (3);
	if (data->matrix[(int)y][(int)(x - 0.005)] != '1' &&
		(data->matrix[(int)(y - 0.005)][(int)x] == '1'
			|| data->matrix[(int)(y + 0.005)][(int)x] == '1') && data->x < x)
		return (4);
	if (rayAngle < 0.5 || rayAngle > 5)
		return (4);
	if (rayAngle >= 0.5 && rayAngle < 2)
		return (2);
	if (rayAngle >= 2 && rayAngle < 3.5)
		return (3);
	if (rayAngle >= 3.5 && rayAngle < 5)
		return (1);
	return (0);
}

int	printwallpixel(t_ray *ray, t_textures *text, int itexture)
{
	int	textx;

	textx = (((ray->ray_x + ray->ray_y) * 64.0)
			- ((int)(ray->ray_x + ray->ray_y) * 64));
	return (gettextcolor(textx, itexture, text));
}

void	gettextstart(t_ray *ray, double *yincrementer, int *itexture)
{
	int	wheigt;

	wheigt = W_HEIGHT / 2 / ray->real_dist;
	*yincrementer = (wheigt * 2) / 64.0;
	if (ray->real_dist >= 1)
	{
		*itexture = 0;
		return ;
	}
	*itexture = (wheigt - W_HEIGHT / 2) / *yincrementer;
	*yincrementer = (ray->wall * 2) / (64.0 - (*itexture) * 2);
}

void	text_pixel_put(t_data *data, t_ray *r, int *y, t_textures *text)
{
	double	d;
	double	yincrementer;
	int		itexture;

	gettextstart(r, &yincrementer, &itexture);
	if (*y == -1)
		(*y)++;
	d = *y;
	while (*y < W_HEIGHT / 2 + r->wall && *y < W_HEIGHT)
	{
		d += yincrementer;
		while (*y <= d && *y < W_HEIGHT)
		{
			my_pixel_put(data->game, r->w_x, *y,
				printwallpixel(r, text, itexture));
			(*y)++;
		}
		itexture++;
	}
}

void	trace_game_line(t_data *data, int orientation, t_ray *r)
{
	int	y;

	r->real_dist = r->dist;
	if (r->dist < 1)
		r->dist = 1;
	r->wall = data->half_w_h / r->dist;
	y = -1;
	while (++y < data->half_w_h - r->wall)
		my_pixel_put(data->game, r->w_x, y, data->ceiling);
	y--;
	if (orientation == 1)
		text_pixel_put(data, r, &y, data->north);
	else if (orientation == 2)
		text_pixel_put(data, r, &y, data->east);
	else if (orientation == 3)
		text_pixel_put(data, r, &y, data->west);
	else if (orientation == 4)
		text_pixel_put(data, r, &y, data->south);
	else if (orientation == 5)
		text_pixel_put(data, r, &y, data->door);
	else if (orientation == 6)
		text_pixel_put(data, r, &y, data->door2);
	y--;
	while (++y < W_HEIGHT)
		my_pixel_put(data->game, r->w_x, y, data->floor);
}

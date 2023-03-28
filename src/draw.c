/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/28 20:10:38 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"


int	get_orientation(t_data *data, double x, double y, double rayAngle) //3 commenta
{
	if (data->matrix[(int)(y + 0.005)][(int)x] != '1' && (data->matrix[(int)y][(int)(x - 0.005)] == '1' || data->matrix[(int)y][(int)(x + 0.005)] == '1') && data->y > y)
		return (1);
	if (data->matrix[(int)(y - 0.005)][(int)x] != '1' && (data->matrix[(int)y][(int)(x - 0.005)] == '1' || data->matrix[(int)y][(int)(x + 0.005)] == '1') && data->y < y)
		return (2);//sud
	if (data->matrix[(int)y][(int)(x + 0.005)] != '1' && (data->matrix[(int)(y - 0.005)][(int)x] == '1' || data->matrix[(int)(y + 0.005)][(int)x] == '1') && data->x > x)
		return (3);//ovest
	if (data->matrix[(int)y][(int)(x - 0.005)] != '1' && (data->matrix[(int)(y - 0.005)][(int)x] == '1' || data->matrix[(int)(y + 0.005)][(int)x] == '1') && data->x < x)
		return (4);//est
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
	//printf("yincr:%f\n", yincrementer);
	while (*y < W_HEIGHT / 2 + r->wall)
	{
		d += yincrementer;
		while (*y <= d)
		{
			my_pixel_put(data->game, r->w_x, *y, printwallpixel(r, text, itexture));
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
	y--;
	while (++y < W_HEIGHT)
		my_pixel_put(data->game, r->w_x, y, data->floor);
}

void	trace_ray(t_data *data, t_image *minimap, double rayAngle, const int x)
{
	double	ray_cos;
	double	ray_sin;
	t_ray	r;

	r.w_x = x;
	rayAngle *= (PI / 180.0);
	ray_cos = cos(rayAngle) / 256;
	ray_sin = sin(rayAngle) / 256;
	r.ray_x = data->x;
	r.ray_y = data->y;
	r.dist = 0.0;
	while (data->matrix[(int)r.ray_y][(int)r.ray_x] != '1' && data->matrix[(int)r.ray_y][(int)r.ray_x] != 'D')
	{
		r.ray_x += ray_cos;
		r.ray_y += ray_sin;
		my_pixel_put(minimap, (int)(r.ray_x * data->r_width), (int) (r.ray_y * data->r_height), 16774656);
	}
	r.dist = sqrt(powf(data->x - r.ray_x, 2) + powf(data->y - r.ray_y, 2));
	r.dist = r.dist * cos((rayAngle - (PI / 180.0) * data->pov));
	//ray_x -= ray_cos;
	//ray_y -= ray_sin;
	if(data->matrix[(int)r.ray_y][(int)r.ray_x] == 'D')
		trace_game_line(data, 5, &r);
	else
		trace_game_line(data, get_orientation(data, r.ray_x, r.ray_y, rayAngle), &r);
}

void	raycasting(t_data *data)
{
	double	rayAngle;
	double	increment;
	int		i;

	rayAngle = data->pov - HALF_FOV;
	increment = (double)FOV / (double)W_WIDTH;
	i = 0;
	while (rayAngle < data->pov + HALF_FOV)
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
				draw_square(data, j * data->r_width, i * data->r_height, 200);
			else if (data->matrix[i][j] == 'D')
				draw_square(data, j * data->r_width, i * data->r_height, 10551296);
			else if (data->matrix[i][j] == 'd')
				draw_square(data, j * data->r_width, i * data->r_height, 65280);
			else
				draw_square(data, j * data->r_width, i * data->r_height, 0);
		}
	}
	draw_circle(data->minimap, data->x * data->r_width - 2.5, data->y * data->r_height - 2.5);
	mlx_put_image_to_window(data->mlx, data->win, data->game->img, 0, 0);
}

void mouse_movements(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->win, &x, &y);
	if (x < W_WIDTH / 2 && x > 0 && y > 0 && y < W_HEIGHT)
		data->pov -= (W_WIDTH / 2 - x) / 100;
	if (x > W_WIDTH / 2 && x < W_WIDTH && y > 0 && y < W_HEIGHT)
		data->pov += (x - W_WIDTH / 2) / 100;
	if (data->pov > 360)
		data->pov -= 360;
	if (data->pov < 0)
		data->pov += 360;
}

int	draw(t_data *data)
{
	mouse_movements(data);
	ft_movements(data);
	draw_minimap(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 10, 10);
	return (0);
}

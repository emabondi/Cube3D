/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/21 12:58:03 by ebondi           ###   ########.fr       */
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

//void	get_tex_start(t_ray *ray, float *t_y)
//{
//	float	w;

//	if (/*ray->wall > W_WIDTH && */ray->dist <= 1)
//	{
//		w = (ray->wall * 2 - W_HEIGHT) / 4;
//		//printf ("w:%f\n", w);
//		//w *= ray->dist;
//		(*t_y) = w;
//		//(*t_y) = abs(w);
//		//printf("wallx2:%d w:%d y:%f\n", (ray->wall *2 ), w, *t_y);
//	}
//}

//void	text_pixel_put(t_data *data, t_ray *r, int *y, t_textures *text)
//{
//	float	t_ratio;
//	float	t_y;
//	float	t_x;
//	int		pixel;

//	// t_pos = (int)ray_x % text->width;
//	//printf("wall:%d\n", r->wall);
//	t_ratio = ((float)text->height / (float)r->wall) / 2;
//	t_y = 0;
//	t_x = (int)((int)(text->width * (r->ray_x + r->ray_y)) % text->width);
//	get_tex_start(r, &t_y);
//	while (++(*y) < data->half_w_h + r->wall && *y < W_HEIGHT)
//	{	
//		pixel = gettextcolor(t_y, t_x, text);
//		t_y += t_ratio;
//		my_pixel_put(data->game, r->w_x, *y, pixel);
//	}
//}
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
	if (ray->dist >= 1)
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
	d = *y;
	while (*y < W_HEIGHT / 2 + r->wall)
	{	
		d += yincrementer;
		while (*y < d)
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
	//r->wall += (int) data->half_w_h / r->dist;
	r->wall = data->half_w_h / r->dist;
	y = -1;
	//printf ("wall:%d, dist:%f\n", r->wall, r->dist);
	//pause();
	while (++y < data->half_w_h - r->wall)
		my_pixel_put(data->game, r->w_x, y, data->ceiling);
	y--;
	if (orientation == 1)
		text_pixel_put(data, r, &y, data->north);
		//while (++y < data->half_w_h + r->wall)
		//	my_pixel_put(data->game, r->w_x, y, 3137239);
	else if (orientation == 2)
		text_pixel_put(data, r, &y, data->east);
		//while (++y < data->half_w_h + r->wall)
		//	 my_pixel_put(data->game, r->w_x, y, 4723712);
	else if (orientation == 3)
		text_pixel_put(data, r, &y, data->west);
		//while (++y < data->half_w_h + r->wall)
		//	 my_pixel_put(data->game, r->w_x, y, 15953948);
	else if (orientation == 4)
		text_pixel_put(data, r, &y, data->south);
		//while (++y < data->half_w_h + r->wall)
		//	 my_pixel_put(data->game, r->w_x, y, 15330053);
	y--;
	while (++y < W_HEIGHT)
		my_pixel_put(data->game, r->w_x, y, data->floor);
}

void	trace_ray(t_data *data, t_image *minimap, double rayAngle, const int x)
{
	double	ray_cos;
	double	ray_sin;
	t_ray	r;
	// double	ray_x;
	// double	ray_y;
	// double	dist;

	r.w_x = x;
	rayAngle *= (PI / 180.0);
	ray_cos = cos(rayAngle) / 256;
	ray_sin = sin(rayAngle) / 256;
	r.ray_x = data->x;
	r.ray_y = data->y;
	r.dist = 0.0;
	while (data->matrix[(int)r.ray_y][(int)r.ray_x] != '1')
	{
		r.ray_x += ray_cos;
		r.ray_y += ray_sin;
		my_pixel_put(minimap, (int)(r.ray_x * data->r_width), (int) (r.ray_y * data->r_height), 16774656);
	}
	r.dist = sqrt(powf(data->x - r.ray_x, 2) + powf(data->y - r.ray_y, 2));
	r.dist = r.dist * cos((rayAngle - (PI / 180.0) * data->pov));
	//ray_x -= ray_cos;
	//ray_y -= ray_sin;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frudello <frudello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:19 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/14 16:37:32 by frudello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"


//int	get_orientation(t_data *data, double x, double y, double rayAngle) //2 commenta
//{
//	if (y < data->y && data->matrix[(int)y][(int)(x - 0.01)] == '1' && data->matrix[(int)y][(int)(x + 0.01)] == '1')
//		return (1);
//	if (y > data->y && data->matrix[(int)y][(int)(x - 0.01)] == '1' && data->matrix[(int)y][(int)(x + 0.01)] == '1')
//		return (2);//sud
//	if (x < data->x && data->matrix[(int)(y - 0.01)][(int)x] == '1' && data->matrix[(int)(y + 0.01)][(int)x]== '1')
//		return (3);//ovest
//	if (x > data->x && data->matrix[(int)(y - 0.01)][(int)x] == '1' && data->matrix[(int)(y + 0.01)][(int)x]== '1')
//		return (4);//est
//	if (rayAngle < 0.5 || rayAngle > 5)
//		return (4);
//	if (rayAngle >= 0.5 && rayAngle < 2)
//		return (2);
//	if (rayAngle >= 2 && rayAngle < 3.5)
//		return (3);
//	if (rayAngle >= 3.5 && rayAngle < 5)
//		return (1);
//	return (0);
//}

//int	get_orientation(t_data *data, double x, double y, double rayAngle) //1 decommenta
//{
//	//(void)data;
//	//(void)x;
//	//(void)y;
//	//(void)rayAngle;
//	if (data->matrix[(int)(y - 0.01)][(int)x] == '1')
//		return (1);
//	else if (data->matrix[(int)(y + 0.01)][(int)x] == '1')
//		return (2);
//	else if (data->matrix[(int)y][(int)(x - 0.01)] == '1')
//		return (3);
//	else if (data->matrix[(int)y][(int)(x + 0.01)] == '1')
//		return (4);
//	else if (rayAngle < 0.5 || rayAngle > 5)
//		return (4);
//	else if (rayAngle >= 0.5 && rayAngle < 2)
//		return (2);
//	else if (rayAngle >= 2 && rayAngle < 3.5)
//		return (3);
//	else if (rayAngle >= 3.5 && rayAngle < 5)
//		return (1);
//	else {
//		printf("rayAngle:%f\n", rayAngle);
//		return (0);
//	}
//}

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
	printf("angle:%f\n", rayAngle);
	return (0);
}

//void	text_pixel_put(t_data *data, int x, int y, t_textures *text, int tex_y, int wall)
//{
//	char	*dst;
//	char	*src;
//	int		color;

//	dst = data->game->addr + (y * data->game->line_length + x * (data->game->bits_per_pixel / 8));
//	if (wall > data->fov * 8)
//		tex_y += (floor(wall - data->fov * 8) / 2);
//	if (text == NULL)
//		*(unsigned int *)dst = 0;
//	else
//	{
//		src = text->addr + ((int)(tex_y * text->height / wall) * text->line_length + x * (text->bpp / 8));
//		color = *(unsigned int *)src;
//		*(unsigned int *)dst = color;
//	}
//}

void	text_pixel_put(t_data *data, t_ray *r, int *y, t_textures *text)
{
	float		t_ratio;
	float		t_y;
	float		t_x;
	int			pixel;

	//	t_pos = (int)ray_x % text->width;
	t_ratio = ((float)text->height / (float)r->wall) / 2;
	t_y = 0;
	t_x = (int)((int)(text->width * (r->ray_x + r->ray_y)) % text->width);
	// gettextstart()
	while (++(*y) < data->half_w_height + r->wall)
	{	
		pixel = gettextcolor(t_y, t_x, text);
		t_y += t_ratio;
		my_pixel_put(data->game, r->w_x, *y, pixel);
	}
}

void	trace_game_line(t_data *data, int orientation, t_ray *r)
{
	// int	wall;
	int	y;

	if (r->dist < 1)
		r->dist = 1;
	r->wall = (int) data->half_w_height / r->dist;
	y = -1;
	while (++y < data->half_w_height - r->wall)
		my_pixel_put(data->game, r->w_x, y, data->ceiling);
	y--;
	if (orientation == 1)
		//while (++y < data->half_w_height + wall)
			text_pixel_put(data, r, &y, data->north);
			//my_pixel_put(data->game, x, y, 3137239);
	else if (orientation == 2)
		while (++y < data->half_w_height + r->wall)
			my_pixel_put(data->game, r->w_x, y, 4723712);
	else if (orientation == 3)
		while (++y < data->half_w_height + r->wall)
			my_pixel_put(data->game, r->w_x, y, 15953948);
	else if (orientation == 4)
		while (++y < data->half_w_height + r->wall)
			my_pixel_put(data->game, r->w_x, y, 15330053);
	y--;
	while (++y < data->w_height)
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

	rayAngle = data->pov - data->half_fov;
	increment = (double)data->fov / (double)data->w_width;
	i = 0;
	while (rayAngle < data->pov + data->half_fov)
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

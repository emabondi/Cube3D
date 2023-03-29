/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:27:59 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/29 19:13:53 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	gettextcolor(int x, int y, t_textures *text)
{
	int		color;
	char	*dst;

	dst = text->addr + (y * text->l_length + x * (text->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	trace_ray2(t_data *data, double rayAngle, t_ray r)
{
	time_t	sec;

	sec = time(NULL);
	r.dist = sqrt(powf(data->x - r.ray_x, 2) + powf(data->y - r.ray_y, 2));
	r.dist = r.dist * cos((rayAngle - (PI / 180.0) * data->pov));
	if (data->matrix[(int)r.ray_y][(int)r.ray_x] == 'D' && sec % 2 == 0)
		trace_game_line(data, 5, &r);
	else if (data->matrix[(int)r.ray_y][(int)r.ray_x] == 'D' && sec % 2 != 0)
		trace_game_line(data, 6, &r);
	else
		trace_game_line(data, get_orientation(data,
				r.ray_x, r.ray_y, rayAngle), &r);
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
	while (data->matrix[(int)r.ray_y][(int)r.ray_x] != '1'
		&& data->matrix[(int)r.ray_y][(int)r.ray_x] != 'D')
	{
		r.ray_x += ray_cos;
		r.ray_y += ray_sin;
		my_pixel_put(minimap, (int)(r.ray_x * data->r_width),
			(int)(r.ray_y * data->r_height), 16774656);
	}
	trace_ray2(data, rayAngle, r);
}

void	raycasting(t_data *data)
{
	double	rayangle;
	double	increment;
	int		i;

	rayangle = data->pov - HALF_FOV;
	increment = (double)FOV / (double)W_WIDTH;
	i = 0;
	while (rayangle < data->pov + HALF_FOV)
	{
		trace_ray(data, data->minimap, rayangle, i);
		rayangle += increment;
		i++;
	}
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

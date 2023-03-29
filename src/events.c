/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:52:13 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/29 19:14:35 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	mouse_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit (0);
}

int	ft_on(int keycode, t_data *data)
{	
	if (keycode == ESC)
		mouse_exit(data);
	if (keycode == W)
		data->w = 1;
	if (keycode == A)
		data->a = 1;
	if (keycode == S)
		data->s = 1;
	if (keycode == D)
		data->d = 1;
	if (keycode == LEFT)
		data->l = 1;
	if (keycode == RIGHT)
		data->r = 1;
	if (keycode == SPACE)
		opening(data);
	return (0);
}

int	ft_off(int keycode, t_data *data)
{
	if (keycode == W)
		data->w = 0;
	if (keycode == A)
		data->a = 0;
	if (keycode == S)
		data->s = 0;
	if (keycode == D)
		data->d = 0;
	if (keycode == LEFT)
		data->l = 0;
	if (keycode == RIGHT)
		data->r = 0;
	return (0);
}

void	ft_move(double angle, t_data *data)
{
	double	rcos;
	double	rsin;

	rcos = cos(angle);
	rsin = sin(angle);
	if (data->matrix[(int)(data->y + rsin * 0.2)]
		[(int)(data->x + rcos * 0.2)] == '1' ||
			data->matrix[(int)(data->y + rsin * 0.07)]
		[(int)(data->x + rcos * 0.07)] == '1' ||
		data->matrix[(int)(data->y + rsin * 0.2)]
		[(int)(data->x + rcos * 0.2)] == 'D')
		return ;
	data->y += rsin * 0.1;
	data->x += rcos * 0.1;
}

void	ft_movements(t_data *data)
{
	if (data->l == 1)
		data->pov -= 2;
	if (data->r == 1)
		data->pov += 2;
	if (data->pov > 360)
		data->pov -= 360;
	else if (data->pov < 0)
		data->pov += 360;
	if (data->w == 1)
		ft_move((data->pov * PI / 180), data);
	if (data->a == 1)
		ft_move((data->pov - 90) * PI / 180, data);
	if (data->s == 1)
		ft_move((data->pov - 180) * PI / 180, data);
	if (data->d == 1)
		ft_move((data->pov - 270) * PI / 180, data);
}

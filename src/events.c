/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:52:13 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/09 19:42:36 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	mouse_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit (0);
	return (0);
}

int	ft_on(int keycode, t_data *data)
{
	//int	x;
	//int	y;

	write (1, "TASTO\n", 6);
	//if (keycode == ESC)
	//	mouse_exit(data);
	if (keycode == W)
		data->map.y += 0.5;
	//if (keycode == A)
	//	data->map.mov[1] = 1;
	//if (keycode == S)
	//	data->map.mov[2] = 1;
	//if (keycode == D)
	//	data->map.mov[3] = 1;
	//if (keycode == LEFT)
	//	data->map.left = 1;
	//if (keycode == RIGHT)
	//	data->map.right = 1;
	printf ("y:%f\n", data->map.y);
	return (0);
}

int	ft_off(int keycode, t_data *data)
{
	//int	x;
	//int	y;

	write (1, "LASCIO\n", 7);
	if (keycode == ESC)
	//	mouse_exit(data);
	//if (keycode == W)
	//	data->map.mov[0] = 0;
	// if (keycode == A)
	// 	data->map.mov[1] = 0;
	//if (keycode == S)
	// 	data->map.mov[2] = 0;
	//if (keycode == D)
	// 	data->map.mov[3] = 0;
	//if (keycode == LEFT)
	//	data->map.left = 0;
	//if (keycode == RIGHT)
	//	data->map.right = 0;
	(void)data;
	return (0);
}
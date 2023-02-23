/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frudello <frudello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:52:13 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/23 14:39:08 by frudello         ###   ########.fr       */
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

	// write (1, "TASTO\n", 6);
	printf("tasto: %d", keycode);
	if (keycode == ESC)
		mouse_exit(data);
	if (keycode == W)
		data->y -= 0.1;
	if (keycode == A)
		data->x -= 0.1;
	if (keycode == S)
		data->y += 0.1;
	if (keycode == D)
		data->x += 0.1;
	// if (keycode == LEFT)
	// 	data->y -= 0.1;
	// if (keycode == RIGHT)
	// 	data->y -= 0.1;
	printf ("y:%f\n", data->y);
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
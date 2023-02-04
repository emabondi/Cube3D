/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:06 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/04 19:03:50 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	window_and_events(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, \
		data->w_width, data->w_height, "Cub3D");
	//mlx_hook(data->mlx.mlx_win, 2, 0, press, rules);
	//mlx_hook(data->mlx.mlx_win, 3, 0, release, rules);
	//mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win , 17, 0, mouse_exit, data);
}

void	ft_init_struct(t_data *data)
{
	data->win = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->w_height = 720;
	data->w_width = 1024;
	data->floor = -1;
	data->ceiling = -1;
	data->map.height = 0;
	data->map.width = 0;
	data->map.pov = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2 || check_name(argv[1]))
		ft_error("Wrong number of arguments or wrong file name");
	ft_init_struct(&data);
	get_info(argv[1], &data);
	check_map(&data.map);
	window_and_events(&data);
	//mlx_loop_hook(data.mlx, draw, &data);
	mlx_loop(data.mlx);
	free_matrix(data.map.matrix);
	exit (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:06 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/02 13:44:00 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	//data->win = mlx_new_window(data->mlx, \
	//	data->w_width, data->w_height, "Cub3D");
	
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
	init_window(&data);
	get_info(argv[1], &data);
	check_map(&data.map);
	return (0);
}

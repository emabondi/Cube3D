/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:06 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/19 19:24:39 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	ft_init_struct(t_data *data)
{
	t_map	map;

	data->mlx = mlx_init();
	data->win = NULL;
	map.height = 0;
	map.width = 0;
	map.pov = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 2 && !check_name(argv[1]))
	{
		ft_init_struct(&data);
		get_info(argv[1], &data);
		// check_map(&data.map);
		data.win = mlx_new_window(data.mlx, data.map.width * 64, \
			data.map.height * 64, "Play your game!");
	}
	else 
		ft_error("Error\nWrong number of arguments or wrong file name\n");
	return (0);
}

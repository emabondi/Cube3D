/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:06 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/20 13:22:59 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	ft_init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->win = NULL;
	data->images->north = NULL;
	data->images->south = NULL;
	data->images->east = NULL;
	data->images->weast = NULL;
	data->images->floor = NULL;
	data->images->ceiling = NULL;
	data->map->height = 0;
	data->map->width = 0;
	data->map->pov = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 2 && !check_name(argv[1]))
	{
		ft_init_struct(&data);
		get_info(argv[1], &data);
		// check_map(&data.map);
		data.win = mlx_new_window(data.mlx, 64,  64, "Play your game!");
		
	}
	else 
		ft_error("Error\nWrong number of arguments or wrong file name\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:06 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/10 20:38:58 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_init_data(t_data *data)
{
	t_map	*map;

	map->height = 0;
	map->width = 0;
	map->matrix = NULL;
	map->pov = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 2 && !check_name(argv[1]))
	{
		ft_init_struct(&data);
		get_map(argv[1], &data);
		// check_map(&data.map);
	}
	else
		return (ft_error("Invalid number of arguments\n"));
	return (0);
}

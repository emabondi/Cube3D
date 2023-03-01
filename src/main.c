/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:06 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/01 20:06:15 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_image	*init_image(void *mlx, int width, int height)
{
	t_image	*new;

	new = (t_image *)malloc(sizeof(t_image));
	new->img = mlx_new_image(mlx, width, height);
	new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel, \
		&new->line_length, &new->endian);
	return (new);
}

void	draw_back(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->w_height)
	{
		j = 0;
		while (j < data->w_width)
		{
			if (i < data->w_height / 2)
				my_pixel_put(data->back, j, i, data->ceiling);
			else
				my_pixel_put(data->back, j, i, data->floor);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->back, 0, 0);
}

void	window_images_events(t_data *data)
{
	data->win = mlx_new_window(data->mlx, \
		data->w_width, data->w_height, "Cub3D");
	mlx_hook(data->win, 2, 0, ft_on, data);
	//mlx_hook(data->win, 3, 0, ft_off, data);
	data->minimap = init_image(data->mlx, data->w_width / 4, data->w_height / 4);
	data->back = init_image(data->mlx, data->w_width, data->w_height);
	data->game = init_image(data->mlx, data->w_width, data->w_height);
	draw_back(data);
	mlx_put_image_to_window(data->mlx, data->win, data->back->img, 0, 0);
	mlx_hook(data->win, 17, 0, mouse_exit, data);
}

void	ft_init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->win = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->w_height = 720;
	data->w_width = 1024;
	data->floor = -1;
	data->ceiling = -1;
	data->height = 0;
	data->width = 0;
	data->r_width = 0;
	data->r_height = 0;
	data->pov = -1;
	data->fov = 60;
	data->half_fov = data->fov / 2;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2 || check_name(argv[1]))
		ft_error("Wrong number of arguments or wrong file name");
	ft_init_struct(&data);
	get_info(argv[1], &data);
	check_map(&data);
	window_images_events(&data);
	mlx_loop_hook(data.mlx, draw, &data);
	mlx_loop(data.mlx);
	free_matrix(data.matrix);
	exit (0);
}

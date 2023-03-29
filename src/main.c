/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:06 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/29 19:09:24 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_image	*init_image(void *mlx, int width, int height)
{
	t_image	*new;

	new = (t_image *)malloc(sizeof(t_image));
	new->img = mlx_new_image(mlx, width, height);
	new->addr = mlx_get_data_addr(new->img, &new->bpp, \
		&new->l_length, &new->endian);
	return (new);
}

void	window_images_events(t_data *data)
{
	data->win = mlx_new_window(data->mlx, \
		W_WIDTH, W_HEIGHT, "Cub3D");
	mlx_hook(data->win, 2, 0, ft_on, data);
	mlx_hook(data->win, 3, 0, ft_off, data);
	data->minimap = init_image(data->mlx, W_WIDTH / 4, W_HEIGHT / 4);
	data->game = init_image(data->mlx, W_WIDTH, W_HEIGHT);
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
	data->alt_dor = 0;
	data->half_w_h = W_HEIGHT / 2;
	data->floor = -1;
	data->ceiling = -1;
	data->height = 0;
	data->width = 0;
	data->r_width = 0;
	data->r_height = 0;
	data->pov = -1;
	data->w = 0;
	data->a = 0;
	data->s = 0;
	data->d = 0;
	data->l = 0;
	data->r = 0;
	data->door = save_info_door("textures/door-copy.xpm", data);
	data->door2 = save_info_door("textures/door-copy2.xpm", data);
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

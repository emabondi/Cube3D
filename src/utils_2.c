/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:48:23 by fgrossi           #+#    #+#             */
/*   Updated: 2023/03/29 19:14:12 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	get_map(t_data *data, char *f, int lines)
{
	int		fd;
	char	*buff;
	int		i;

	fd = open(f, O_RDONLY);
	if (fd == -1)
		ft_error("No such file or directory");
	buff = get_next_line(fd);
	i = lines - data->height;
	while (--i > 1)
	{
		free (buff);
		buff = get_next_line(fd);
	}
	free(buff);
	ft_malloc_map(data, fd);
	close(fd);
}

void	mouse_movements(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->win, &x, &y);
	if (x < W_WIDTH / 2 && x > 0 && y > 0 && y < W_HEIGHT)
		data->pov -= (W_WIDTH / 2 - x) / 100;
	if (x > W_WIDTH / 2 && x < W_WIDTH && y > 0 && y < W_HEIGHT)
		data->pov += (x - W_WIDTH / 2) / 100;
	if (data->pov > 360)
		data->pov -= 360;
	if (data->pov < 0)
		data->pov += 360;
}

void	draw_minimap(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->matrix[++i] != NULL)
	{
		j = -1;
		while (data->matrix[i][++j] != '\0')
		{
			if (data->matrix[i][j] == '1')
				draw_square(data, j * data->r_width, i * data->r_height, 200);
			else if (data->matrix[i][j] == 'D')
				draw_square(data, j * data->r_width,
					i * data->r_height, 10551296);
			else if (data->matrix[i][j] == 'd')
				draw_square(data, j * data->r_width, i * data->r_height, 65280);
			else
				draw_square(data, j * data->r_width, i * data->r_height, 0);
		}
	}
	draw_circle(data->minimap,
		data->x * data->r_width - 2.5, data->y * data->r_height - 2.5);
	mlx_put_image_to_window(data->mlx, data->win, data->game->img, 0, 0);
}

void	opening(t_data *data)
{
	if (data->matrix[(int)(data->y + 1)][(int)(data->x)] == 'D')
		data->matrix[(int)(data->y + 1)][(int)(data->x)] = 'd';
	else if (data->matrix[(int)(data->y + 1)][(int)(data->x)] == 'd')
		data->matrix[(int)(data->y + 1)][(int)(data->x)] = 'D';
	if (data->matrix[(int)(data->y)][(int)(data->x + 1)] == 'D')
		data->matrix[(int)(data->y)][(int)(data->x + 1)] = 'd';
	else if (data->matrix[(int)(data->y)][(int)(data->x + 1)] == 'd')
		data->matrix[(int)(data->y)][(int)(data->x + 1)] = 'D';
	if (data->matrix[(int)(data->y - 1)][(int)(data->x)] == 'D')
		data->matrix[(int)(data->y - 1)][(int)(data->x)] = 'd';
	else if (data->matrix[(int)(data->y - 1)][(int)(data->x)] == 'd')
		data->matrix[(int)(data->y - 1)][(int)(data->x)] = 'D';
	if (data->matrix[(int)(data->y)][(int)(data->x - 1)] == 'D')
		data->matrix[(int)(data->y)][(int)(data->x - 1)] = 'd';
	else if (data->matrix[(int)(data->y)][(int)(data->x - 1)] == 'd')
		data->matrix[(int)(data->y)][(int)(data->x - 1)] = 'D';
}

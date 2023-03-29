/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:11:35 by fgrossi           #+#    #+#             */
/*   Updated: 2023/03/29 19:18:52 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	parse_line(char *str, t_data *data)
{
	int	i;

	i = ft_skip_spaces(str);
	if (!ft_strncmp(str + i, "NO ", 3))
		data->north = save_info(str + i, data, data->north);
	else if (!ft_strncmp(str + i, "SO ", 3))
		data->south = save_info(str + i, data, data->south);
	else if (!ft_strncmp(str + i, "WE ", 3))
		data->west = save_info(str + i, data, data->west);
	else if (!ft_strncmp(str + i, "EA ", 3))
		data->east = save_info(str + i, data, data->east);
	else if (!ft_strncmp(str + i, "F ", 2) \
		|| !ft_strncmp(str + i, "C ", 2))
		get_colors(str + i, data);
	else if (str[0] == '\n')
		return ;
	else if (str[i] == '1' && map_at_eof(data))
		parse_line_2(data, str);
	else
		ft_error("Invalid line in file");
}

void	get_info(char *f, t_data *data)
{
	int		fd;
	char	*str;
	int		lines;

	fd = open(f, O_RDONLY);
	if (fd == -1)
		ft_error("No such file or directory");
	lines = 1;
	str = get_next_line(fd);
	while (str != NULL)
	{
		parse_line(str, data);
		free (str);
		str = get_next_line(fd);
		lines++;
	}
	close(fd);
	data->r_width = W_WIDTH / 4 / data->width;
	data->r_height = W_HEIGHT / 4 / data->height;
	get_map(data, f, lines);
}

void	copy_char(t_data *data, char b, int *o, int *i)
{
	int	tmp;

	if (b == 9)
	{
		tmp = *o + 4;
		while (*o < tmp)
		{
			data->matrix[*i][*o] = ' ';
			(*o)++;
		}
	}
	else
	{
		data->matrix[*i][*o] = b;
		(*o)++;
	}
}

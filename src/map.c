/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:24:15 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/24 19:58:06 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	check_rgb(char *str, int *rgb)
{
	int		i;
	int		count;
	char	**colors;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		else if (!ft_isdigit(str[i]) && str[i] != '\n' && str[i + 1] != '\0')
			ft_error("Invalid digit rgb");
		i++;
	}
	if (count != 2)
		ft_error("Invalid count rgb");
	colors = ft_split(str, ',');
	i = 0;
	while (colors[i] != NULL)
	{
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			ft_error("Invalid value rgb");
		i++;
	}
}

void	get_colors(char *str, t_data *data)
{
	int		i;
	int		color;
	int		rgb[3];

	i = ft_skip_spaces(str + 1) + 1;
	check_rgb(str + i, rgb);
	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (str[0] == 'F')
		data->images->floor = color;
	else
		data->images->ceiling = color;
}

void	save_info(char *str, t_data *data)
{
	char	*str2;
	int		i;
	int		fd;

	str2 = ft_strchr(str, ' ');
	i = ft_skip_spaces(str2);
	fd = open(str2 + i, O_RDONLY);
	if (!fd)
		ft_error("Couldn't get the textures");
	close(fd);
	i = 128;
	if (str[0] == 'N')
		data->images->north = mlx_xpm_file_to_image(data->mlx, str2, &i, &i);
	else if (str[0] == 'S')
		data->images->south = mlx_xpm_file_to_image(data->mlx, str2, &i, &i);
	else if (str[0] == 'E')
		data->images->east = mlx_xpm_file_to_image(data->mlx, str2, &i, &i);
	else if (str[0] == 'W')
		data->images->weast = mlx_xpm_file_to_image(data->mlx, str2, &i, &i);
}

void	parse_line(char *str, t_data *data)
{
	int	i;
	int	len;

	i = ft_skip_spaces(str);
	printf("%s", str + i);
	if (!ft_strncmp(str + i, "NO ", 3) \
		|| !ft_strncmp(str + i, "SO ", 3) \
		|| !ft_strncmp(str + i, "WE ", 3) \
		|| !ft_strncmp(str + i, "EA ", 3))
		save_info(str + i, data);
	else if (!ft_strncmp(str + i, "F ", 2) \
		|| !ft_strncmp(str + i, "C ", 2))
		get_colors(str + i, data);
	else if (str[0] == '\n')
		return ;
	else if (str[i] == '1' && map_at_eof(data))
	{
		data->map->height++;
		len = ft_strlen(str);
		if (len > data->map->width)
			data->map->width = len;
	}
	else
		ft_error("Invalid line in file");
	printf("Colors: %d %d\n", data->images->ceiling, data->images->floor);
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
	//printf("%d %d\n", data->map->height, data->map->width);
	close(fd);
	//get_map(data, f, lines);
}

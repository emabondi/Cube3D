/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:24:15 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/23 18:05:11 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	get_colors(char *str, t_data *data)
{
	return (r << 16) | (g << 8) | r;
		ciao;
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

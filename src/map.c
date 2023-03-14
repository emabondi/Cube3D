/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:24:15 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/14 18:04:07 by gmeoli           ###   ########.fr       */
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
		if (str[i] == ',' && ft_isdigit(str[i + 1]))
			count++;
		else if (!ft_isdigit(str[i]) && str[i] != '\n' && str[i + 1] != '\0')
			ft_error("Invalid digit rgb");
		i++;
	}
	if (count != 2)
		ft_error("Invalid rgb");
	colors = ft_split(str, ',');
	i = 0;
	while (colors[i] != NULL)
	{
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			ft_error("Invalid value rgb");
		i++;
	}
	free_matrix(colors);
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
		data->floor = color;
	else
		data->ceiling = color;
}

t_textures	*save_info(char *str, t_data *data, t_textures *check)
{
	char		*str2;
	t_textures	*ret;

	if (check != NULL)
		ft_error("Double definition of texture");
	str2 = ft_strchr(str, ' ');
	str2 += ft_skip_spaces(str2);
	str2[ft_strlen(str2) - 1] = '\0';
	ret = (t_textures *)malloc(sizeof(t_textures));
	ret->ptr = mlx_xpm_file_to_image(data->mlx, str2, &ret->width, &ret->height);
	if (!ret->ptr)
		ft_error("Unvalid texture");
	ret->addr = mlx_get_data_addr(ret->ptr, &ret->bpp,
			&ret->l_length, &ret->endian);
	return (ret);
}

void	parse_line_2(t_data *data, char *str)
{
	int	len;
	int	i;

	data->height++;
	len = ft_strlen(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == 9)
			len += 3;
	}
	if (ft_strchr(str, '\n') != NULL)
		len--;
	if (len > data->width)
		data->width = len;
}

void	parse_line(char *str, t_data *data)
{
	int	i;
	//int	len;

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
	{
		parse_line_2(data, str);
		//data->height++;
		//len = ft_strlen(str);
		//printf("len: %d\n", len);
		//if (ft_strchr(str, '\n') != NULL)
		//	len--;
		//if (len > data->width)
		//	data->width = len;
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
	close(fd);
	data->r_width = W_WIDTH / 4 / data->width;
	data->r_height = W_HEIGHT / 4 / data->height;
	get_map(data, f, lines);
}

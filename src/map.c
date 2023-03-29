/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:24:15 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/29 19:12:21 by fgrossi          ###   ########.fr       */
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
	i = -1;
	while (colors[++i] != NULL)
	{
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			ft_error("Invalid value rgb");
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
	ret->ptr = mlx_xpm_file_to_image(data->mlx,
			str2, &ret->width, &ret->height);
	if (!ret->ptr)
		ft_error("Unvalid texture");
	ret->addr = mlx_get_data_addr(ret->ptr, &ret->bpp,
			&ret->l_length, &ret->endian);
	return (ret);
}

t_textures	*save_info_door(char *str, t_data *data)
{
	t_textures	*ret;

	ret = (t_textures *)malloc(sizeof(t_textures));
	ret->ptr = mlx_xpm_file_to_image(data->mlx, str, &ret->width, &ret->height);
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

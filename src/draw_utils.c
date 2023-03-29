/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:17:15 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/29 18:50:36 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	my_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->l_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *data, int x, int y, int c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->r_height)
	{
		j = -1;
		while (++j < data->r_width)
			my_pixel_put(data->minimap, x + j, y + i, c);
	}
}

void	draw_circle(t_image *image, float x, float y)
{
	int	i;
	int	j;
	int	o;
	int	tot;

	i = -1;
	o = 2;
	while (++i < 7)
	{
		j = 0;
		tot = 7 - (o * 2);
		while (j < o)
			j++;
		while (tot > 0)
		{
			my_pixel_put(image, x + j, y + i, 16449536);
			j++;
			tot--;
		}
		if (i < 2)
			o--;
		else if (i > 3)
			o++;
	}
}

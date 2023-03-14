/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:27:59 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/14 18:16:36 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	gettextcolor(int x, int y, t_textures *text)
{
	int		color;
	char	*dst;

	dst = text->addr + (y * text->l_length + x * (text->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

// void	gettextstart(t_ray *ray, int x, )
// {
// 	int		w_height;
// 	double	y_incrementer;
	
// 	w_height = W_HEIGHT / 2 / ray->dist;
// 	y_incrementer = (W_HEIGHT * 2) / 128.0;
// 	if (ray->dist >= 1)
// 	{
// 		ray->itexture = 0;
// 		return ;
// 	}
// 	ray->itexture = (W_HEIGHT - W_HEIGHT / 2) / y_incrementer;
// 	y_incrementer = (ray->wall * 2) / (128.0 - ray->itexture * 2);
// }
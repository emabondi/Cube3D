/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frudello <frudello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:27:59 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/14 16:37:41 by frudello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	gettextcolor(int x, int y, t_textures *text)
{
	int		color;
	char	*dst;

	dst = text->addr + (y * text->line_length + x * (text->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

// void	gettextstart(t_ray *ray, int x, )
// {
// 	int		wheight;
// 	double yincrementer;
	
// 	wheight = W_HEIGHT / 2 / ray->dist;
// 	yincrementer = (wheight * 2) / 128.0;
// 	if (ray->dist >= 1)
// 	{
// 		ray->itexture = 0;
// 		return ;
// 	}
// 	ray->itexture = (wheight - W_HEIGHT / 2) / yincrementer;
// 	yincrementer = (ray->wall * 2) / (128.0 - ray->itexture * 2);
// }
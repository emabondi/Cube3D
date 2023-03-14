/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:27:59 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/14 14:17:38 by ebondi           ###   ########.fr       */
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
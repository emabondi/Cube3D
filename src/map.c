/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:24:15 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/19 16:20:53 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	get_map(char *f, t_data *data)
{
	int	fd;
	(void)data;

	fd = open(f, O_RDONLY);
	if (fd == -1)
		ft_error("Error: No such file or directory\n");
	while (get_next_line(fd))
	{
		// check_map(); 
	}
}

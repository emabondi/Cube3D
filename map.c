/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:24:15 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/09 19:03:27 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int check_map()
{
	
}

void	check_name(char *f)
{
	int	len;

	len = ft_strlen(f);
	if (len < 4 || f[len - 1] != 'b' || f[len - 2] != 'u' \
			|| f[len - 3] != 'c' || f[len - 4] != '.')
		ft_error("File extension not valid!\n");
}

void	get_map(char *f, t_data *data)
{
	int	fd;
	(void)data;

	check_ext_name(f);
	fd = open(f, O_RDONLY);
	if (fd == -1)
		ft_error("Error: No such file or directory\n");
	while (get_next_line(fd))
	{
		check_map(); 
	}
}

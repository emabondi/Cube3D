/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:24:15 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/19 20:33:58 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	get_info(char *f, t_data *data)
{
	int	fd;
	char *str;
	
	(void)data;
	
	fd = open(f, O_RDONLY);
	if (fd == -1)
		ft_error("Error: No such file or directory\n");
	str = get_next_line(fd);
	while (str != NULL)
	{
		//if (str[0] == '\n')
		//	printf("ciao");
		//printf("%s", str);
		free (str);
		str = get_next_line(fd);
	}
}

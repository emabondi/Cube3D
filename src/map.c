/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:24:15 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/20 15:41:30 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

//void save_info();

void	parse_line(char *str, t_data *data)
{
	int	i;

	(void)data;
	i = ft_skip_spaces(str);
	if (!ft_strncmp(str + i, "NO ", 3) && data->images->north == NULL)
		save_info();
}

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
		parse_line(str, data);
		free (str);
		str = get_next_line(fd);
	}
}

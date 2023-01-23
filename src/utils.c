/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:46:48 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/23 17:59:02 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	map_at_eof(t_data *data)
{
	if (data->images->south != NULL \
		&& data->images->north != NULL \
		&& data->images->east != NULL \
		&& data->images->weast != NULL \
		&& data->images->floor != -1 \
		&& data->images->ceiling != -1)
		return (1);
	else
		ft_error("Invalid line in file");
}

int	ft_skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	return (i);
}

int	ft_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit(0);
}

int	check_name(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4 || str[len - 1] != 'b' || str[len - 2] != 'u' \
			|| str[len - 3] != 'c' || str[len - 4] != '.')
		return (1);
	return (0);
}

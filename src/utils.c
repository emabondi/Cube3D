/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:46:48 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/29 17:57:28 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	free_matrix(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i] != NULL)
		free(mat[i]);
	free(mat);
}

int	map_at_eof(t_data *data)
{
	if (data->north != NULL \
		&& data->south != NULL \
		&& data->west != NULL \
		&& data->east != NULL \
		&& data->floor != -1 \
		&& data->ceiling != -1)
		return (1);
	else
		ft_error("Invalid line in file");
	return (0);
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

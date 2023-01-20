/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:46:48 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/20 17:29:22 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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

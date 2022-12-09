/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:06 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/09 17:58:42 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (ft_error("Invalid number of arguments\n"));
	get_map(argv[1], &data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:16 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/09 17:12:56 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_image
{
	
}			t_image;

typedef struct s_data
{
	t_image	image;
}			t_data;

//utils
int		ft_error(char *str);

//map
void	get_map(char *f, t_data *data);
void	check_name(char *fd);

#endif
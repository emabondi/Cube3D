/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:16 by ebondi            #+#    #+#             */
/*   Updated: 2022/12/09 18:33:47 by gmeoli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>

typedef struct s_images {
	int			img_width;
	int			img_height;
	void		*SO;
	void		*NO;
	void		*EA;
	void		*WE;
}	t_images;

typedef struct s_map {
	int			width;
	int			height;
	char		**matrix;
	void		*F;
	void		*C;
	int			pov;
}	t_map;

typedef struct s_data {
	t_images	images;
	t_map		map;
}	t_data;

//utils
int				ft_error(char *str);

//map
void			get_map(char *f, t_data *data);
void			check_name(char *fd);

#endif

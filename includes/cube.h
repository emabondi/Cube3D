/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:16 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/26 16:40:41 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"

typedef struct s_images {
	void	*ptr;
	void	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_images;

typedef struct s_map {
	int			width;
	int			height;
	char		**matrix;
	int			pov;
}	t_map;

typedef struct s_data {
	t_images	*north;
	t_images	*south;
	t_images	*west;
	t_images	*east;
	//t_images	*door;
	void		*mlx;
	void		*win;
	int			w_height;
	int			w_width;
	int		floor;
	int		ceiling;
	t_images	images;
	t_map		map;
}	t_data;

//utils
int		ft_error(char *str);
int		check_name(char *str);
int		ft_skip_spaces(char *str);
int		map_at_eof(t_data *data);

//map
void	get_info(char *f, t_data *data);

#endif

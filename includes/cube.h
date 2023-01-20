/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:16 by ebondi            #+#    #+#             */
/*   Updated: 2023/01/20 13:26:32 by ebondi           ###   ########.fr       */
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
	//int	img_width;
	//int	img_height;
	char	*south;
	char	*north;
	char	*east;
	char	*weast;
	int		*floor;
	int		*ceiling;
}	t_images;

typedef struct s_map {
	int			width;
	int			height;
	char		**matrix;
	int			pov;
}	t_map;

typedef struct s_data {
	void		*mlx;
	void		*win;
	t_images	*images;
	t_map		*map;
}	t_data;

//utils
int				ft_error(char *str);
int				check_name(char *str);
int				ft_skip_spaces(char *str);

//map
void			get_info(char *f, t_data *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:16 by ebondi            #+#    #+#             */
/*   Updated: 2023/02/04 20:12:23 by ebondi           ###   ########.fr       */
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

typedef struct s_textures {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_textures;

typedef struct s_map {
	int			width;
	int			height;
	char		**matrix;
	char		pov;
}	t_map;

typedef struct s_data {
	t_textures	*north;
	t_textures	*south;
	t_textures	*west;
	t_textures	*east;
	//t_textures	*door;
	void		*mlx;
	void		*win;
	int			w_height;
	int			w_width;
	int			floor;
	int			ceiling;
	t_textures	*images; //puttana
	t_map		map;
}	t_data;

//utils
int		ft_error(char *str);
int		check_name(char *str);
int		ft_skip_spaces(char *str);
int		map_at_eof(t_data *data);
void	free_matrix(char **mat);

//map
void	get_info(char *f, t_data *data);
void	get_map(t_data *data, char *f, int lines);
void	check_map(t_map *map);

//events
int		mouse_exit(t_data *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:16 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/07 16:24:51 by gmeoli           ###   ########.fr       */
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
//# include "../mlx/mlx.h"
#include <mlx.h>

# define PI		3.14159265359f
//keypress
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124
# define ESC	53

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_textures {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_textures;

//typedef struct s_map {
//	int			width;
//	int			height;
//	char		**matrix;
//	int			pov;
//	float		x;
//	float		y;
//}	t_map;

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
	int			half_w_height;
	int			floor;
	int			ceiling;

	//map
	int			width;
	int			height;
	int			r_width;
	int			r_height;
	char		**matrix;
	double		pov;
	int			fov;
	int			half_fov;
	float		x;
	float		y;
	t_image		*minimap;
	t_image		*game;

	//movements
	int			w;
	int			a;
	int			s;
	int			d;
	int			l;
	int			r;
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
void	check_map(t_data *map);

//events
int		mouse_exit(t_data *data);
int		ft_on(int keycode, t_data *data);
int		ft_off(int keycode, t_data *data);
void	ft_movements(t_data *data);

//draw
int		draw(t_data *data);
void	my_pixel_put(t_image *image, int x, int y, int color);
void	draw_square(t_data *data, int x, int y, int c);
void	draw_circle(t_image *image, float x, float y);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:25:16 by ebondi            #+#    #+#             */
/*   Updated: 2023/03/29 19:35:22 by ebondi           ###   ########.fr       */
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
# include <time.h>
//# include "../mlx/mlx.h"
# include <mlx.h>

# define PI 		3.14159265359f
//keypress <
# define W			13
# define A			0
# define S			1
# define D			2
# define LEFT		123
# define RIGHT		124
# define SPACE	    49
// >
# define ESC		53
# define W_HEIGHT	1080
# define W_WIDTH	1920
# define FOV		60
# define HALF_FOV	30

typedef struct s_image {
	void		*img;
	char		*addr;
	int			bpp;
	int			l_length;
	int			endian;
}	t_image;

typedef struct s_textures {
	void		*ptr;
	char		*addr;
	int			bpp;
	int			l_length;
	int			endian;
	int			width;
	int			height;
}	t_textures;

typedef struct s_ray {
	double		ray_x;
	double		ray_y;
	double		dist;
	double		real_dist;
	int			w_x;
	int			wall;
}	t_ray;

typedef struct s_data {
	t_textures	*north;
	t_textures	*south;
	t_textures	*west;
	t_textures	*east;
	t_textures	*door;
	t_textures	*door2;
	void		*mlx;
	void		*win;
	int			half_w_h;
	int			floor;
	int			ceiling;
	int			alt_dor;
	int			width;
	int			height;
	int			r_width;
	int			r_height;
	char		**matrix;
	double		pov;
	float		x;
	float		y;
	t_image		*minimap;
	t_image		*game;
	int			w;
	int			a;
	int			s;
	int			d;
	int			l;
	int			r;
}	t_data;

//utils
int				ft_error(char *str);
int				check_name(char *str);
int				ft_skip_spaces(char *str);
int				map_at_eof(t_data *data);
void			free_matrix(char **mat);
t_textures		*save_info_door(char *str, t_data *data);
void			ft_malloc_map(t_data *data, int fd);
void			trace_game_line(t_data *data, int orientation, t_ray *r);
int				get_orientation(t_data *data,
					double x, double y, double rayAngle);
void			mouse_movements(t_data *data);
void			draw_minimap(t_data *data);
void			opening(t_data *data);
t_textures		*save_info(char *str, t_data *data, t_textures *check);
void			parse_line_2(t_data *data, char *str);
void			get_colors(char *str, t_data *data);
void			copy_char(t_data *data, char b, int *o, int *i);

//map
void			get_info(char *f, t_data *data);
void			get_map(t_data *data, char *f, int lines);
void			check_map(t_data *map);

//events
int				mouse_exit(t_data *data);
int				ft_on(int keycode, t_data *data);
int				ft_off(int keycode, t_data *data);
void			ft_movements(t_data *data);
int				mlx_mouse_get_pos(void *win_ptr, int *x, int *y);

//draw
int				draw(t_data *data);
void			my_pixel_put(t_image *image, int x, int y, int color);
void			draw_square(t_data *data, int x, int y, int c);
void			draw_circle(t_image *image, float x, float y);
int				gettextcolor(int x, int y, t_textures *text);

#endif

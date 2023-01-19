# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmeoli <gmeoli@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 15:02:44 by ebondi            #+#    #+#              #
#    Updated: 2023/01/19 16:18:45 by gmeoli           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAMEBONUS = cub3D_bonus
LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a
SRCSFLS = main.c check_map.c map.c read_map.c utils.c
SRCS = $(addprefix src/, $(SRCSFLS))
SRCSFLSBONUS = check_validity.c draw_line_texture.c fill_matrix.c free_all.c ft_doors.c ft_mouse.c game.c minimap.c minimap2.c parse_map.c various_inits.c init_and_utils.c init_and_utils2.c loops_move.c raycasting.c utils6.c utils2.c
SRCSBONUS = $(addprefix bonus/src/, $(SRCSFLSBONUS))
OBJS = $(SRCS:.c=.o)
HDRS = cub3d.h
FLAGS = -Wall -Werror -Wextra
COMPILER = -l mlx -framework openGL -framework AppKit

all: $(NAME)

bonus: $(NAMEBONUS)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(LIBFT) $(MLX)
	@gcc $(FLAGS) $(SRCS) $(LIBFT) $(MLX) $(COMPILER) -o $(NAME)
	@printf "\033[1;35mCub3D compiled!!\e[0m\n"

$(NAMEBONUS): $(LIBFT) $(MLX)
	@gcc $(FLAGS) $(SRCSBONUS) $(LIBFT) $(MLX) $(COMPILER) -o $(NAMEBONUS)

clean:
	@rm -f $(OBJS)
	@make clean -C ./libft

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(NAMEBONUS)
	@make fclean -C ./libft
	@printf "\033[1;91mRemoving objects...\n"

re:			fclean all

.PHONY:		all clean fclean re bonus

vai: re
	@./$(NAME)

leaks:
	@leaks --atExit -- ./$(NAME)

.PHONY:	all clean fclean re bonus vai leaks
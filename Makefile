# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 15:02:44 by ebondi            #+#    #+#              #
#    Updated: 2023/03/29 19:33:27 by ebondi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAMEBONUS = cub3D_bonus
LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a
SRCSFLS = main.c check_map.c map.c utils.c events.c draw.c draw_utils.c draw2.c utils_2.c garbage.c
SRCS = $(addprefix src/, $(SRCSFLS))
OBJS = $(SRCSFLS:.c=.o)
GNLFLS = get_next_line.c get_next_line_utils.c
GNLSRCS = $(addprefix get_next_line/, $(GNLFLS))
GNLOBJS = $(GNLFLS:.c=.o)
#SRCSFLSBONUS =
#SRCSBONUS = $(addprefix bonus/src/, $(SRCSFLSBONUS))
#HDRS = cub3d.h
FLAGS = -Wall -Werror -Wextra
MLXFLAGS = -l mlx -framework openGL -framework AppKit

all: $(NAME)

bonus: $(NAMEBONUS)

$(LIBFT):
	@$(MAKE) -C ./libft

$(MLX):
	@$(MAKE) -C ./mlx

$(NAME): $(LIBFT) $(MLX) $(SRCS) $(GNLSRCS)
	@gcc -c $(FLAGS) $(SRCS) $(GNLSRCS)
	@gcc -g $(OBJS) $(GNLOBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@printf "\033[1;35mCub3D compiled!!\e[0m\n"

#$(NAMEBONUS): $(LIBFT) $(MLX)
#	@gcc $(FLAGS) $(SRCSBONUS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAMEBONUS)

clean:
	@printf "\033[0;33mRemoving objects..."
	@rm -f $(OBJS) $(GNLOBJS)
	@make clean -C ./libft
	@make clean -C ./mlx
	@printf "\033[1;32mDone!\n"

fclean:	clean
	@printf "\033[1;91mRemoving executables..."
	@rm -f $(NAME)
#	@rm -f $(NAMEBONUS)
	@make fclean -C ./libft
	@printf "\033[1;32mDone!\n"

re:	fclean all

vai: $(NAME)
	@./$(NAME) maps/map1.cub

leaks:
	@leaks --atExit -- ./$(NAME) maps/map1.cub

.PHONY:	all clean fclean re bonus vai leaks
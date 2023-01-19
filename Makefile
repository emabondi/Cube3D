# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 15:02:44 by ebondi            #+#    #+#              #
#    Updated: 2023/01/19 18:21:46 by ebondi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAMEBONUS = cub3D_bonus
LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a
SRCSFLS = main.c check_map.c map.c read_map.c utils.c
SRCS = $(addprefix src/, $(SRCSFLS))
GNLSRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRCSFLSBONUS =
SRCSBONUS = $(addprefix bonus/src/, $(SRCSFLSBONUS))
OBJS = $(SRCS:.c=.o)
HDRS = cub3d.h
FLAGS = -Wall -Werror -Wextra
COMPILER = -l mlx -framework openGL -framework AppKit

all: $(NAME)

bonus: $(NAMEBONUS)

$(LIBFT):
	@$(MAKE) -C ./libft

$(NAME): $(LIBFT) $(MLX)
	@gcc $(FLAGS) $(SRCS) $(GNLSRCS) $(LIBFT) $(MLX) $(COMPILER) -o $(NAME)
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

vai: re
	@./$(NAME)

leaks:
	@leaks --atExit -- ./$(NAME)

.PHONY:	all clean fclean re bonus vai leaks
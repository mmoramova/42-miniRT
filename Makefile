# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 18:55:47 by josorteg          #+#    #+#              #
#    Updated: 2023/12/09 19:40:02 by josorteg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
HEADER = inc/miniRT.h
C_FLAGS = -Wall -Wextra -Werror -g -MMD
L_FRAME = -framework OpenGL -framework AppKit
RM = rm -f

#------------------------------LIBRARIES---------------------------------------#

LIBFT = ./libs/libft
MLIB = ./libs/minilibx_opengl_20191021
SRC_LIBFT = libs/libft/libft.a
MAKE_LIBFT = make -C libs/libft bonus --no-print-directory
SRC_MLX = libs/minilibx_opengl_20191021/libmlx.a
MAKE_MLX = make -C libs/minilibx_opengl_20191021 --no-print-directory

#------------------------------SOURCES-----------------------------------------#
SRC_FILES = miniRT set_scene set_objects set_objects2 rgb \
		vector vector2 utils free draw mlx \
		intersection ray check_objects check_objects2 \
		check_input check_input2 set_color

SRC = $(addsuffix .c, $(SRC_FILES))
F_OBJ = obj/
OBJ = $(addprefix $(F_OBJ), $(SRC:.c=.o))
DEP = $(addprefix $(F_OBJ), $(SRC:.c=.d))

#------------------------------COLORS-----------------------------------------#
BLACK = \033[0;39m
BLUE = \033[0;94m
GREEN = \033[0;92m
MAGENTA = \033[0;95m

#------------------------------EXECUTION-----------------------------------------#
all: dir make_libs make_mlx $(NAME)

make_libs:
	@echo "$(BLUE)Libft:$(BLACK)"
	@$(MAKE_LIBFT)

make_mlx:
	@echo "$(MAGENTA)Mlx:$(BLACK)"
	@$(MAKE_MLX)
	@echo "$(MAGENTA)No actions needed.$(BLACK)"

-include ${DEP}

vpath %.c src/

dir:
	@mkdir -p $(F_OBJ)

$(F_OBJ)%.o: %.c Makefile
	$(CC) $(C_FLAGS) -I ./inc -I $(LIBFT) -I $(MLIB) -c $< -o $@


$(NAME)::
	@echo "$(GREEN)MiniRT:$(BLACK)"

$(NAME):: $(OBJ) $(SRC_LIBFT) $(SRC_MLX)
	$(CC) $(C_FLAGS) $(^) $(L_FRAME) -o $(NAME)
	@echo "$(GREEN)Everything has been compilated.$(BLACK)"

$(NAME)::
	@echo "$(GREEN)No actions needed.$(BLACK)"

.PHONY: all clean fclean re

clean:
	$(RM) $(OBJ) $(DEP)
	$(RM) -R obj
	$(MAKE_LIBFT) clean
	$(MAKE_MLX) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE_LIBFT) fclean
	$(MAKE_MLX) clean
	@echo "$(MAGENTA)Everything has been cleaned.$(BLACK)"

re: fclean all

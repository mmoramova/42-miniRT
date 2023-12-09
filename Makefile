# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 09:49:08 by josorteg          #+#    #+#              #
#    Updated: 2023/12/09 12:32:23 by mmoramov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
RM = rm -rf
LIBC = ar -rcs
FLAGS = -g -O3 -Wall -Wextra -Werror

#------------------------------SORUCES-----------------------------------------#

SRC_FILES = miniRT set_scene set_objects set_objects2 rgb \
		vector vector2 utils free draw mlx set_screen \
		intersection ray check_objects check_objects2 \
		check_input set_color
SRC = $(addsuffix .c, $(SRC_FILES))
PATH_SRC = ./src/
LIBFT = ./libs/libft/
MLIB = ./libs/minilibx_opengl_20191021/
LIBA = $(LIBFT)libft.a
MLIBA = $(MLIB)libmlx.a
L_FRAME = -framework OpenGL -framework AppKit
INC = 	-I ./inc/\
		-I $(MLIB)\
		-I $(LIBFT)

#------------------------------DIRECTORIES------------------------------------#

F_OBJ = $(PATH_SRC)obj/
OBJ = $(addprefix $(F_OBJ), $(SRC:.c=.o))
DEP = $(addprefix $(F_OBJ), $(SRC:.c=.d))

#------------------------------MAKE RULES-------------------------------------#

all : dir $(NAME)
-include $(DEP)

dir:
	@make -C $(LIBFT) bonus
	@make -C $(MLIB)
	@mkdir -p $(F_OBJ)

$(F_OBJ)%.o:$(PATH_SRC)%.c
	@$(CC) -MMD $(FLAGS) -c $< -o $@ $(INC)
$(NAME): $(OBJ) dir
	@$(CC) $(FLAGS) $(OBJ) $(LIBA) $(MLIBA) $(L_FRAME) -o $(NAME) $(INC)

#---------------------------------CLEAN---------------------------------------#

.PHONY: clean fclean re

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT)

clean:
	$(RM) ./src/obj
	make clean -C $(MLIB)
	make clean -C $(LIBFT)

re: fclean all


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 09:49:08 by josorteg          #+#    #+#              #
#    Updated: 2023/11/11 13:26:36 by mmoramov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
RM = rm -rf
LIBC = ar -rcs
FLAGS = -Wall -Wextra -Werror -g -O3

#------------------------------SORUCES-----------------------------------------#

SRC = main.c
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
	@make -C $(LIBFT)
	@make -C $(MLIB)
	@mkdir -p $(F_OBJ)
#	@mkdir -p $(F_OBJ)frac
#	@mkdir -p $(F_OBJ)menu

$(F_OBJ)%.o:$(PATH_SRC)%.c
	@$(CC) -MMD $(FLAGS) -c $< -o $@ $(INC)
$(NAME): $(OBJ)
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


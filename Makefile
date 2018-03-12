# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/08 19:11:03 by eebersol          #+#    #+#              #
#    Updated: 2018/03/12 15:38:19 by eebersol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Define the program

NAME			= ft_nm

NAME_OTOOL		= ft_otool

LIB				=	./libft/libft.a

_SRC			= init_struct.c \
					handle.c \
					nm_otool.c \
					data_magic.c \
					print.c \
					tools.c \
					type.c \
					segment.c \
					endian.c \
					value_nm.c \
					value_otool.c \

INCLUDES		= -I./libft/includes/ -I./includes/

SRC				= $(addprefix srcs/,$(_SRC))

OBJ				= $(SRC:.c=.o)

CFLAGS			= -Wall -Wextra -Werror -fsanitize=address -g

all: $(NAME) $(NAME_OTOOL)

$(NAME): $(OBJ)
	@make -C ./libft/
	@gcc $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES) -o $(NAME)
	@echo $(NAME) " : compiled"

$(NAME_OTOOL): $(OBJ)
	@make -C ./libft/
	@gcc $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES) -o $(NAME_OTOOL)
	@echo $(NAME_OTOOL) ": compiled"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@echo "Clean all .o files"

fclean:	clean
	@make fclean -C libft
	@/bin/rm -rf $(NAME)
	@/bin/rm -rf $(NAME_OTOOL)
	@echo "Clean all .o and .a"

re: fclean all

.PHONY: clean fclean re

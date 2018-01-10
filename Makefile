# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/08 19:11:03 by eebersol          #+#    #+#              #
#    Updated: 2018/01/10 17:04:09 by eebersol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Define the program

NAME			= Nm-otool

LIB				=	./libft/libft.a

_SRC			= main.c \
					init_struct.c \
					nm.c \
					fat.c \
					magic.c \
					swap.c \
					print.c \
					get.c \
					tools.c \


INCLUDES		= -I./libft/includes/ -I./includes/

SRC				= $(addprefix srcs/,$(_SRC))

OBJ				= $(SRC:.c=.o)

CFLAGS			= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft/
	@gcc $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES) -ltermcap -o $(NAME)
	@echo $(NAME)" compiled"


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)


clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@echo "Clean all .o files"

fclean:	clean
	@make fclean -C libft
	@/bin/rm -rf $(NAME)
	@echo "Clean all .o and .a"

re: fclean all

exec : all
	@echo "\t\t\t\x1B[33m*** Test executable file ***\x1B[0m\n\n"
	@./$(NAME) $(NAME)
	@./$(NAME) $(NAME) > test_executable ; nm -o $(NAME) > test_executable_true
	@diff test_executable test_executable_true; if [ $$? -eq 0 ] ; then echo "\nYour executable : \x1B[32mSUCCESS\x1B[0m\n" ; fi
	@diff test_executable test_executable_true; if [ $$? -eq 1 ] ; then echo "\nYour executable : \x1B[31mERROR\x1B[0m\n" ; fi

fat	: all
	@echo "\t\t\t\x1B[33m*** Test fat file ***\x1B[0m\n\n"
	@./$(NAME) /usr/lib/bundle1.o
	@./$(NAME) /usr/lib/bundle1.o > test_fat ; nm -o /usr/lib/bundle1.o > test_fat_true
	@diff test_fat test_fat_true; if [ $$? -eq 0 ] ; then echo "\n/usr/bin/fat : \x1B[32mSUCCESS\x1B[0m\n" ; fi
	@diff test_fat test_fat_true; if [ $$? -eq 1 ] ; then echo "\n/usr/bin/fat : \x1B[31mERROR\x1B[0m\n" ; fi

perl : all
	@echo "\t\t\t\x1B[33m*** Test perl file ***\x1B[0m\n\n"
	@./$(NAME) /usr/bin/perl
	@./$(NAME) /usr/bin/perl > test_perl ; nm -o /usr/bin/perl > test_perl_true
	@diff test_perl test_perl_true; if [ $$? -eq 0 ] ; then echo "\n/usr/bin/perl : \x1B[32mSUCCESS\x1B[0m\n" ; fi
	@diff test_perl test_perl_true; if [ $$? -eq 1 ] ; then echo "\n/usr/bin/perl : \x1B[31mERROR\x1B[0m\n" ; fi

python : all
	@echo "\t\t\t\x1B[33m*** Test python file ***\x1B[0m\n\n"
	@./$(NAME) /usr/bin/python
	@./$(NAME) /usr/bin/python > test_python ; nm -o /usr/bin/python > test_python_true
	@diff test_python test_python_true; if [ $$? -eq 0 ] ; then echo "\n/usr/bin/python : \x1B[32mSUCCESS\x1B[0m\n" ; fi
	@diff test_python test_python_true; if [ $$? -eq 1 ] ; then echo "\n/usr/bin/python : \x1B[31mERROR\x1B[0m\n" ; fi

multiple : all
	@echo "\t\t\t\x1B[33m*** Test multiple argument ***\x1B[0m\n\n"
	@./$(NAME) init_struct.o malloc.o
	@./$(NAME) init_struct.o malloc.o > test_multiple_arg ; nm -o init_struct.o malloc.o > test_multiple_arg_true
	@./$(NAME) init_struct.o malloc.o > tmp; if [ $$? -eq 1 ] ;  then echo "\nMutiple arg : \x1B[31mERROR\x1B[0m return value false" ; fi
	@diff test_multiple_arg test_multiple_arg_true; if [ $$? -eq 0 ] ; then echo "\nMutiple arg : \x1B[32mSUCCESS\x1B[0m\n" ; fi
	@diff test_multiple_arg test_multiple_arg_true; if [ $$? -eq 1 ] ; then echo "\n/Multiple arg : \x1B[31mERROR\x1B[0m\n" ; fi

testNm : all exec fat perl python multiple

.PHONY: clean fclean re
	
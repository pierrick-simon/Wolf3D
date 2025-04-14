##
## EPITECH PROJECT, 2025
## Wol3D
## File description:
## Makefile
##

MAIN = src/main.c

SRC =

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

NAME =	wolf3d

CPPFLAGS = -iquoteinclude -iquotelib

CFLAGS = -Wall -Wextra -g3

LDFLAGS = -Llib

LDLIBS = -lmy

all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./lib
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./lib clean

fclean:		clean
	$(RM) $(NAME) $(TESTS)*
	$(MAKE) -C ./lib fclean

re: fclean all

.PHONY: all clean fclean re

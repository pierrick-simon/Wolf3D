##
## EPITECH PROJECT, 2025
## Wolf3D
## File description:
## Makefile
##

MAIN = src/main.c

SRC =	src/creat_window.c	\
		src/event.c	\
		src/move_rect.c	\
		src/sys_loop.c	\
		src/ray_cast.c	\
		src/move_player.c	\
		src/is_keyboard_input.c	\
		src/init/init_game.c \
		src/init/init_sys.c	\
		src/init/init_struct.c	\
		src/destroy/destroy_game.c \
		src/destroy/destroy_sys.c	\
		src/destroy/destroy_struct.c	\
		src/game/event.c	\
		src/game/draw_game.c	\

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

NAME =	wolf3d

CPPFLAGS = -iquoteinclude -iquotelib

CFLAGS = -Wall -Wextra -g3

LDFLAGS = -Llib

LDLIBS = -lmy

CSFMLFLAG = -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./lib
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS) $(LDFLAGS) $(CSFMLFLAG)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./lib clean

fclean:		clean
	$(RM) $(NAME)
	$(MAKE) -C ./lib fclean

re: fclean all

.PHONY: all clean fclean re

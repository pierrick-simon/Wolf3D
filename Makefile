##
## EPITECH PROJECT, 2025
## Wolf3D
## File description:
## Makefile
##

MAIN = src/main.c

SRC =	$(addprefix src/,					\
			init/creat_window.c				\
			events/event.c					\
			algo/move_rect.c				\
			sys_loop.c						\
			algo/ray_cast.c					\
			algo/move_player.c				\
			events/is_keyboard_input.c		\
			init/init_game.c 				\
			init/init_menu.c 				\
			init/init_pause.c 				\
			init/init_setting.c 			\
			init/init_sys.c					\
			init/init_struct.c				\
			init/init_from_conf.c			\
			destroy/destroy_game.c 			\
			destroy/destroy_menu.c 			\
			destroy/destroy_pause.c 		\
			destroy/destroy_setting.c 		\
			destroy/destroy_sys.c			\
			destroy/destroy_struct.c		\
			destroy/free_draw_textbox.c		\
			game/event.c					\
			game/draw_game.c				\
			menu/event.c					\
			menu/draw_menu.c				\
			pause/event.c					\
			pause/draw_pause.c				\
			draw_func.c                     \
			setting/event.c					\
			setting/draw_setting.c			\
		)

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

##
## EPITECH PROJECT, 2025
## Wolf3D
## File description:
## Makefile
##

MAIN = src/main.c

SRC =	$(addprefix src/,					\
			\
			sys_loop.c						\
			load_screen.c					\
			draw_func.c                     \
			\
			$(addprefix algo/,				\
				move_rect.c					\
				cast_single_ray.c			\
				cast_rays.c					\
				cast_pos.c					\
				move_player.c				\
			)								\
			$(addprefix init/,				\
				create_window.c				\
				init_sys.c					\
				init_struct.c				\
				init_from_conf.c			\
			)								\
			$(addprefix destroy/,			\
				destroy_sys.c				\
				destroy_struct.c			\
				free_draw_textbox.c			\
			)								\
			$(addprefix menu/,				\
				init_menu.c 				\
				destroy_menu.c 				\
				menu_event.c				\
				draw_menu.c					\
			)								\
			$(addprefix pause/,				\
				init_pause.c 				\
				destroy_pause.c 			\
				pause_event.c				\
				draw_pause.c				\
			)								\
			$(addprefix settings/,			\
				init_settings.c 			\
				destroy_settings.c 			\
				settings_event.c			\
				draw_settings.c				\
			)								\
			$(addprefix game/,				\
				game_event.c				\
				draw_game.c					\
				destroy_game.c 				\
				init_game.c 				\
				init_weapon.c 				\
				update.c 					\
			)								\
			$(addprefix save/,				\
				check.c			 			\
				free_map.c			 		\
				get_save.c			 		\
				add_node_file.c				\
				free_node_file.c			\
				sort_node_file.c			\
				get_file.c					\
				update_list.c				\
				draw_save.c					\
			)								\
			$(addprefix levels/,			\
				levels_event.c				\
				draw_levels.c				\
				destroy_levels.c			\
				init_levels.c				\
			)								\
			$(addprefix events/,			\
				is_input.c					\
				sys_event.c					\
			)								\
		)

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

NAME =	wolf3d

CPPFLAGS = -iquoteinclude -iquotelib

CFLAGS = -Wall -Wextra

LDFLAGS = -Llib -Llib/linked_list

LDLIBS = -lmy -llinked_list

CSFMLFLAG = -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./lib
	$(MAKE) -C ./lib/linked_list
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS) $(LDFLAGS) $(CSFMLFLAG)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./lib clean
	$(MAKE) -C ./lib/linked_list clean

fclean:		clean
	$(RM) $(NAME)
	$(MAKE) -C ./lib fclean
	$(MAKE) -C ./lib/linked_list fclean

re: fclean all

.PHONY: all clean fclean re

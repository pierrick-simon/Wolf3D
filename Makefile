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
			check_env.c						\
			\
			$(addprefix algo/,				\
				move_rect.c					\
				move_y.c					\
				get_color.c					\
				draw_entities.c				\
				sort_entities.c				\
				center_ray.c				\
				get_pourcentage.c			\
				cast_single_ray.c			\
				cast_rays.c					\
				cast_pos.c					\
				move_player.c				\
				enemies_movement.c			\
				enemies_algo.c				\
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
			$(addprefix difficulty/,		\
				init_difficulty.c 			\
				destroy_difficulty.c 		\
				difficulty_event.c			\
				draw_difficulty.c			\
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
				show_game_environement.c	\
				game_event.c				\
				draw_game.c					\
				destroy_game.c 				\
				init_game.c 				\
				init_render_state.c			\
				init_weapon.c 				\
				update.c 					\
				shot.c 						\
				update_weapon.c 			\
				update_save.c 				\
				draw_mini_map.c 			\
				draw_minimap_elements.c		\
				init_toolbar.c				\
				handle_items.c  			\
				handle_boss.c  				\
				handle_projectiles.c 		\
				add_projectile.c 			\
				explode_wall.c 				\
			)								\
			$(addprefix save/,				\
				$(addprefix list/,			\
					add_node_file.c			\
					free_node_file.c		\
					sort_node_file.c		\
					add_node_entity.c		\
				)							\
				check_save.c 				\
				check.c			 			\
				free_map.c			 		\
				get_save.c			 		\
				get_file.c					\
				update_list.c				\
				draw_save.c					\
				save_score.c				\
				save_map.c 					\
				init_mini_map_color.c 		\
				free_mini_map_color.c 		\
			)								\
			$(addprefix levels/,			\
				levels_event.c				\
				draw_levels.c				\
				destroy_levels.c			\
				init_levels.c				\
			)								\
			$(addprefix choose/,			\
				choose_event.c				\
				draw_choose.c				\
				destroy_choose.c			\
				init_choose.c				\
			)								\
			$(addprefix edit_info/,			\
				edit_info_event.c			\
				draw_edit_info.c			\
				destroy_edit_info.c			\
				init_edit_info.c			\
			)								\
			$(addprefix edit_map/,			\
				edit_map_event.c			\
				draw_edit_map.c				\
				destroy_edit_map.c			\
				init_edit_map.c				\
				iso.c 						\
				find_tile.c 				\
				draw_button.c				\
				map_event.c 				\
				click_buttons.c				\
				add_node_history.c 			\
				generate_map.c				\
				generate_calcul.c			\
				generate_room.c				\
			)								\
			$(addprefix your_maps/,			\
				your_maps_event.c			\
				draw_your_maps.c			\
				destroy_your_maps.c			\
				init_your_maps.c			\
			)								\
			$(addprefix events/,			\
				is_input.c					\
				sys_event.c					\
			)								\
			$(addprefix map/,				\
				event.c						\
				draw_map.c					\
				destroy_map.c				\
				init_map.c					\
			)								\
			$(addprefix score/,				\
				event.c						\
				draw_score.c				\
				destroy_score.c				\
				init_score.c				\
				get_score.c 				\
				free_info_score.c           \
				sort_score.c				\
			)								\
			$(addprefix leave/,				\
				event.c						\
				draw_leave.c				\
				destroy_leave.c				\
				init_leave.c				\
			)								\
			$(addprefix win/,				\
				win_event.c					\
				draw_win.c					\
				destroy_win.c				\
				init_win.c					\
			)								\
			$(addprefix lose/,				\
				lose_event.c				\
				draw_lose.c					\
				destroy_lose.c				\
				init_lose.c					\
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

debug:	CFLAGS+=-g3
debug:	fclean $(OBJ)
	$(MAKE) -C ./lib CFLAGS+=-g3
	$(MAKE) -C ./lib/linked_list CFLAGS+=-g3
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

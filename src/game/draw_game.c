/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_loop
*/

#include <math.h>
#include "save.h"
#include "game.h"

void draw_game(system_t *sys, void *structure)
{
    game_t *game = (game_t *)structure;

    update_all(sys, game);
    sfMusic_pause(sys->music);
    if (sfMusic_getStatus(sys->save->music) == sfStopped
        || sfMusic_getStatus(sys->save->music) == sfPaused)
        sfMusic_play(sys->save->music);
    game_events(sys, game);
    sfRenderWindow_clear(sys->window, sfWhite);
    show_game_environement(sys, game);
    sfRenderWindow_display(sys->window);
    update_time_end(game->time_info);
}

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_loop
*/

#include <math.h>
#include <stdlib.h>
#include "save.h"
#include "game.h"

static void handle_music(system_t *sys, game_t *game)
{
    sfSoundStatus music = sfMusic_getStatus(sys->save->music);
    sfSoundStatus boss = sfMusic_getStatus(game->music[BOSS_MUSIC]);

    sfMusic_pause(sys->music);
    if (sys->save->boss->head == NULL) {
        sfMusic_pause(game->music[BOSS_MUSIC]);
        if (music == sfStopped || music == sfPaused)
            sfMusic_play(sys->save->music);
    } else {
        sfMusic_pause(sys->save->music);
        if (boss == sfStopped || boss == sfPaused)
            sfMusic_play(game->music[BOSS_MUSIC]);
    }
}

void draw_game(system_t *sys, void *structure)
{
    game_t *game = (game_t *)structure;

    update_all(sys, game);
    handle_music(sys, game);
    game_events(sys, game);
    sfRenderWindow_clear(sys->window, sfWhite);
    show_game_environement(sys, game);
    sfRenderWindow_display(sys->window);
    empty_linked_list(sys->save->boss, free);
    update_time_end(game->time_info);
}

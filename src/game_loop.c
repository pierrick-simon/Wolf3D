/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_loop
*/

#include "wolf.h"

static void shot_gun_anim(game_t *game, shotgun_t *shotgun)
{
    int current = sfClock_getElapsedTime(game->clock).microseconds;
    double diff = (double)(current - shotgun->shot) / SEC_IN_MICRO;

    for (int i = 0; i < SHOTGUN_NB_TILE; i++) {
        if (diff > SHOTGUN_FRAME * i
            && diff < SHOTGUN_FRAME * (i + 1)
            && shotgun->sprite.tile == i) {
            move_rect(&shotgun->sprite, SHOTGUN_SPRITE.x, SHOTGUN_NB_TILE);
            shotgun->sprite.tile++;
            break;
        }
    }
    if (shotgun->sprite.tile == SHOTGUN_NB_TILE)
        shotgun->sprite.tile = 0;
}

void game_loop(game_t *game, shotgun_t *shotgun)
{
    while (sfRenderWindow_isOpen(game->window) == sfTrue) {
        events(game, shotgun);
        shot_gun_anim(game, shotgun);
        sfRenderWindow_clear(game->window, sfWhite);
        if (sfMusic_getStatus(game->music) == sfStopped)
            sfMusic_play(game->music);
        sfRenderWindow_drawSprite(game->window, shotgun->sprite.sprite, NULL);
        sfRenderWindow_display(game->window);
    }
}

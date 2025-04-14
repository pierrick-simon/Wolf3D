/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_loop
*/

#include "wolf.h"

static void shot_gun_anim(game_t *game, weapon_t *weapon)
{
    int current = sfClock_getElapsedTime(game->clock).microseconds;
    double diff = (double)(current - weapon->shot) / SEC_IN_MICRO;

    for (int i = 0; i < SHOTGUN_NB_TILE; i++) {
        if (diff > SHOTGUN_FRAME * i
            && diff < SHOTGUN_FRAME * (i + 1)
            && weapon->sprite.tile == i) {
            move_rect(&weapon->sprite, SHOTGUN_SPRITE_X, SHOTGUN_NB_TILE);
            weapon->sprite.tile++;
            break;
        }
    }
    if (weapon->sprite.tile == SHOTGUN_NB_TILE)
        weapon->sprite.tile = 0;
}

void game_loop(game_t *game, weapon_t *weapon)
{
    while (sfRenderWindow_isOpen(game->window) == sfTrue) {
        events(game, weapon);
        shot_gun_anim(game, weapon);
        sfRenderWindow_clear(game->window, sfWhite);
        if (sfMusic_getStatus(game->music) == sfStopped)
            sfMusic_play(game->music);
        sfRenderWindow_drawSprite(game->window, weapon->sprite.sprite, NULL);
        sfRenderWindow_display(game->window);
    }
}

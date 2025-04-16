/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** free
*/

#include "wolf.h"
#include <stdlib.h>

void destroy_weapon(weapon_t *weapon)
{
    for (int i = 0; i < NB_WEAPON; i++) {
        if (weapon->texture != NULL && weapon->texture[i] != NULL)
            sfTexture_destroy(weapon->texture[i]);
        if (weapon->sound != NULL && weapon->sound[i] != NULL)
            sfMusic_destroy(weapon->sound[i]);
    }
    if (weapon->texture != NULL)
        free(weapon->texture);
    if (weapon->sound != NULL)
        free(weapon->sound);
    if (weapon->sprite.sprite != NULL)
        sfSprite_destroy(weapon->sprite.sprite);
}

void destroy_game(game_t *game)
{
    if (game->music != NULL)
        sfMusic_destroy(game->music);
    if (game->clock != NULL)
        sfClock_destroy(game->clock);
    if (game->window != NULL)
        sfRenderWindow_destroy(game->window);
}

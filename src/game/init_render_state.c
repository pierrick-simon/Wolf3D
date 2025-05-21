/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_render_state.c
*/

#include "game.h"
#include "element.h"

int init_render_state(game_t *game)
{
    for (size_t i = 0; i < NB_ENEMIES; ++i) {
        game->state_enemies[i] = (sfRenderStates){0};
        game->state_enemies[i].texture =
            sfTexture_createFromFile(ENEMY[i].path, NULL);
        if (game->state_enemies[i].texture == NULL)
            return ERROR;
        game->state_enemies[i].transform = sfTransform_Identity;
        game->state_enemies[i].blendMode = sfBlendAlpha;
    }
    return SUCCESS;
}

/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_render_state.c
*/

#include "game.h"
#include "entities.h"

int init_render_state(game_t *game)
{
    for (size_t i = 0; i < NB_ENTITIES; ++i) {
        game->state_entities[i] = (sfRenderStates){0};
        game->state_entities[i].texture =
            sfTexture_createFromFile(ENTITY[i].path, NULL);
        if (game->state_entities[i].texture == NULL)
            return ERROR;
        game->state_entities[i].transform = sfTransform_Identity;
        game->state_entities[i].blendMode = sfBlendAlpha;
    }
    return SUCCESS;
}

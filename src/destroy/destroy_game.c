/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** free
*/

#include "wolf.h"
#include <stdlib.h>

static void destroy_player(player_t *player)
{
    sfCircleShape_destroy(player->crossair->circle);
    free(player->crossair);
    free(player);
}

static void destroy_weapon(weapon_t *weapon)
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
    if (weapon->sprite != NULL) {
        if (weapon->sprite->sprite != NULL)
            sfSprite_destroy(weapon->sprite->sprite);
        free(weapon->sprite);
    }
    free(weapon);
}

static void destroy_map(map_t *map)
{
    if (map->wall_state.texture != NULL)
        sfTexture_destroy((sfTexture *)map->wall_state.texture);
    if (map->ceiling_floor != NULL)
        sfRectangleShape_destroy(map->ceiling_floor);
    free(map);
}

static void destroy_time_info(time_info_t *time_info)
{
    sfClock_destroy(time_info->clock);
    free(time_info);
}

void destroy_game(void *structure)
{
    game_t *game = (game_t *)structure;

    if (game->weapon != NULL)
        destroy_weapon(game->weapon);
    if (game->player != NULL)
        destroy_player(game->player);
    if (game->map != NULL)
        destroy_map(game->map);
    if (game->time_info != NULL)
        destroy_time_info(game->time_info);
    free(game);
}

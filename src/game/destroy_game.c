/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** free
*/

#include "game.h"
#include <stdlib.h>

static void destroy_player(player_t *player)
{
    if (player->crossair != NULL)
        sfCircleShape_destroy(player->crossair);
    free(player);
}

static void destroy_weapon(weapon_t *weapon)
{
    for (int i = 0; i < NB_WEAPON; i++) {
        if (weapon->info != NULL && weapon->info[i].texture != NULL)
            sfTexture_destroy(weapon->info[i].texture);
        if (weapon->info != NULL && weapon->info[i].sound != NULL)
            sfMusic_destroy(weapon->info[i].sound);
    }
    if (weapon->info != NULL)
        free(weapon->info);
    if (weapon->sprite != NULL)
        sfSprite_destroy(weapon->sprite);
    if (weapon->empty != NULL)
        sfMusic_destroy(weapon->empty);
    free(weapon);
}

static void destroy_map(map_t *map)
{
    for (size_t i = 0; i < NB_WALL_TXT; ++i)
        if (map->wall_states[i].texture != NULL)
            sfTexture_destroy((sfTexture *)map->wall_states[i].texture);
    if (map->ceiling_floor != NULL)
        sfRectangleShape_destroy(map->ceiling_floor);
    free(map);
}

static void destroy_time_info(time_info_t *time_info)
{
    sfClock_destroy(time_info->clock);
    free(time_info);
}

static void destroy_tool(toolbar_t *tool)
{
    if (tool->draw != NULL)
        free_draw_textbox(tool->draw, -1);
    if (tool->head != NULL) {
        if (tool->head->texture != NULL)
            sfTexture_destroy(tool->head->texture);
        if (tool->head->sprite != NULL)
            sfSprite_destroy(tool->head->sprite);
        free(tool->head);
    }
    if (tool->rectangle != NULL)
        sfRectangleShape_destroy(tool->rectangle);
    if (tool->background != NULL)
        sfTexture_destroy(tool->background);
    free(tool);
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
    if (game->tool != NULL)
        destroy_tool(game->tool);
    for (int i = 0; i < NB_MUSIC; i++) {
        if (game->music[i] != NULL)
            sfMusic_destroy(game->music[i]);
    }
    free(game);
}

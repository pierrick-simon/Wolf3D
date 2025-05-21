/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** free
*/

#include "game.h"
#include "linked_list.h"
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

static void destroy_map_info(map_t *map)
{
    sfTexture_destroy((sfTexture *)map->wall_states.texture);
    if (map->ceiling_floor != NULL)
        sfRectangleShape_destroy(map->ceiling_floor);
    free(map);
}

static void destroy_time_info(time_info_t *time_info)
{
    sfClock_destroy(time_info->clock);
    free(time_info);
}

static void destroy_tool_sprite(toolbar_t *tool)
{
    if (tool->head != NULL) {
        if (tool->head->texture != NULL)
            sfTexture_destroy(tool->head->texture);
        if (tool->head->sprite != NULL)
            sfSprite_destroy(tool->head->sprite);
        free(tool->head);
    }
    if (tool->flashlight != NULL) {
        if (tool->flashlight->texture != NULL)
            sfTexture_destroy(tool->flashlight->texture);
        if (tool->flashlight->sprite != NULL)
            sfSprite_destroy(tool->flashlight->sprite);
        free(tool->flashlight);
    }
}

static void destroy_tool(toolbar_t *tool)
{
    if (tool->draw != NULL)
        free_draw_textbox(tool->draw, -1);
    destroy_tool_sprite(tool);
    if (tool->rectangle != NULL)
        sfRectangleShape_destroy(tool->rectangle);
    if (tool->background != NULL)
        sfTexture_destroy(tool->background);
    if (tool->border != NULL)
        sfTexture_destroy(tool->border);
    free(tool);
}

static void destroy_light(light_t *light)
{
    if (light->night_render != NULL)
        sfRenderTexture_destroy(light->night_render);
    if (light->night != NULL)
        sfSprite_destroy(light->night);
    if (light->overlay != NULL)
        sfRectangleShape_destroy(light->overlay);
    if (light->flashlight != NULL)
        sfCircleShape_destroy(light->flashlight);
    free(light);
}

static void destroy_music_rectangle(sfMusic **music,
    sfRectangleShape *mini_map, sfCircleShape *cursor)
{
    for (int i = 0; i < NB_MUSIC; i++) {
        if (music[i] != NULL)
            sfMusic_destroy(music[i]);
    }
    if (mini_map != NULL)
        sfRectangleShape_destroy(mini_map);
    if (cursor != NULL)
        sfCircleShape_destroy(cursor);
}

void destroy_game(void *structure)
{
    game_t *game = (game_t *)structure;

    destroy_music_rectangle(game->music, game->mini_map, game->cursor);
    if (game->weapon != NULL)
        destroy_weapon(game->weapon);
    if (game->player != NULL)
        destroy_player(game->player);
    if (game->map != NULL)
        destroy_map_info(game->map);
    if (game->time_info != NULL)
        destroy_time_info(game->time_info);
    if (game->tool != NULL)
        destroy_tool(game->tool);
    if (game->light != NULL)
        destroy_light(game->light);
    for (size_t i = 0; i < NB_ENTITIES; ++i)
        sfTexture_destroy((sfTexture *)game->state_entities[i].texture);
    free(game);
}

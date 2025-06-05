/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_minimap_elements
*/

#include "game.h"
#include "save.h"
#include "entities.h"
#include <math.h>

void draw_look(system_t *sys, sfRectangleShape *mini_map)
{
    float angle_center = DEG(sys->save->info->start_angle) - RIGHT_ANGLE;
    sfVector2f center = {
        MINI_MAP_BORDER + MINI_MAP_SIZE / 2,
        MINI_MAP_BORDER + MINI_MAP_SIZE / 2};

    sfRectangleShape_setSize(mini_map,
        (sfVector2f){MINI_MAP_RAY, MINI_MAP_TILE});
    sfRectangleShape_setFillColor(mini_map, sfGreen);
    sfRectangleShape_setPosition(mini_map, (sfVector2f){center.x, center.y});
    sfRectangleShape_setOrigin(mini_map, (sfVector2f){MINI_MAP_RAY / 2, 0});
    for (int i = -MINI_MAP_OFFSET; i <= MINI_MAP_OFFSET; i++) {
        sfRectangleShape_setRotation(
            mini_map, angle_center + i * MINI_MAP_FOV);
        sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
    }
    sfRectangleShape_setRotation(mini_map, 0);
    sfRectangleShape_setOrigin(mini_map, (sfVector2f){0, 0});
}

void draw_center(system_t *sys, sfCircleShape *cursor)
{
    sfCircleShape_setPosition(cursor, (sfVector2f){(float)MINI_MAP_SIZE /
        2 + MINI_MAP_BORDER, (float)MINI_MAP_SIZE
        / 2 + MINI_MAP_BORDER});
    sfCircleShape_setFillColor(cursor, sfBlack);
    sfRenderWindow_drawCircleShape(sys->window, cursor, NULL);
}

void draw_square(
    system_t *sys, sfRectangleShape *mini_map, sfVector2i *player_tile)
{
    sfVector2f pos = {0, 0};
    sfVector2f size = {MINI_MAP_TILE, MINI_MAP_TILE};
    float offset_x = MINIOFF((int)sys->save->info->start_pos.x);
    float offset_y = MINIOFF((int)sys->save->info->start_pos.y);

    for (int i = -MINI_MAP_OFFSET; i <= MINI_MAP_OFFSET; i++) {
        for (int j = -MINI_MAP_OFFSET; j <= MINI_MAP_OFFSET; j++) {
            pos.x = MINI_MAP_BORDER + (j + MINI_MAP_OFFSET)
                * MINI_MAP_TILE - offset_x;
            pos.y = MINI_MAP_BORDER + (i + MINI_MAP_OFFSET)
                * MINI_MAP_TILE - offset_y;
            sfRectangleShape_setFillColor(mini_map, sys->save->mini_map
                [player_tile->y + i + MINI_MAP_OFFSET]
                [player_tile->x + j + MINI_MAP_OFFSET]);
            sfRectangleShape_setSize(mini_map, size);
            sfRectangleShape_setPosition(mini_map, pos);
            sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
        }
    }
}

static sfBool is_in_minimap(sfVector2i *player_tile, sfVector2i *tile)
{
    if (player_tile->x - MINI_MAP_OFFSET > tile->x
        || player_tile->x + MINI_MAP_OFFSET < tile->x
        || player_tile->y - MINI_MAP_OFFSET > tile->y
        || player_tile->y + MINI_MAP_OFFSET < tile->y)
        return sfFalse;
    return sfTrue;
}

static void distance_to_player(
    sfVector2f *player_pos, sfVector2f *pos, sfVector2f *mini_map_pos)
{
    sfVector2f center = {(float)MINI_MAP_SIZE /
        2 + MINI_MAP_BORDER, (float)MINI_MAP_SIZE
        / 2 + MINI_MAP_BORDER};

    mini_map_pos->x = (pos->x - player_pos->x) * MINI_MAP_TILE
        / TILE_SIZE + center.x;
    mini_map_pos->y = (pos->y - player_pos->y) * MINI_MAP_TILE
        / TILE_SIZE + center.y;
}

static void color_item(entity_t *tmp, sfCircleShape *cursor)
{
    if (tmp->type < NB_ITEM)
        sfCircleShape_setFillColor(cursor, sfBlue);
    if (tmp->type >= NB_ITEM && tmp->type < E_BOSS_PROJECTILE)
        sfCircleShape_setFillColor(cursor, sfRed);
    if (tmp->type >= E_BOSS_PROJECTILE)
        sfCircleShape_setFillColor(cursor, ORANGE);
}

void draw_minimap_entities(system_t *sys, linked_list_t *list,
    sfVector2i *player_tile, sfCircleShape *cursor)
{
    sfVector2i entity_tile = {0};
    entity_t *tmp = NULL;
    sfVector2f pos = {0};

    for (node_t *head = list->head; head != NULL; head = head->next) {
        tmp = head->data;
        entity_tile = (sfVector2i){floor(tmp->pos.x / TILE_SIZE),
            floor(tmp->pos.y / TILE_SIZE)};
        if (is_in_minimap(player_tile, &entity_tile) == sfFalse
            || tmp->is_alive == sfFalse)
            continue;
        distance_to_player(&sys->save->info->start_pos, &tmp->pos, &pos);
        sfCircleShape_setPosition(cursor, pos);
        color_item(tmp, cursor);
        sfRenderWindow_drawCircleShape(sys->window, cursor, NULL);
    }
}

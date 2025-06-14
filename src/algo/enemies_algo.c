/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** enemies_algo
*/

#include "entities.h"
#include "game.h"
#include "save.h"
#include <math.h>
#include <stdlib.h>

void get_angle(
    float *angle, sfVector2f *first, sfVector2f *second, float current_dist)
{
    float dist = fabs(first->x - second->x) / current_dist;
    float diff_x = first->x - second->x;
    float diff_y = first->y - second->y;

    if (dist > 1)
        dist = 1;
    if (dist < -1)
        dist = -1;
    *angle = asin(dist);
    if (diff_y > 0) {
        if (diff_x > 0)
            *angle = M_PI / 2 - *angle;
        else
            *angle += M_PI / 2;
    } else {
        if (diff_x > 0)
            *angle = (M_PI / 2 - *angle) * -1;
        else
            *angle = (M_PI / 2 + *angle) * -1;
    }
}

sfBool is_wall_between(game_t *game, entity_t *enemy)
{
    player_t tmp = {0};
    intersection_t type = {0};
    sfVector2f intersection_point = {0};
    float value = 0;

    type.type = NONE;
    tmp.save = game->player->save;
    tmp.pos = enemy->pos;
    if (enemy->dist < 1)
        return sfFalse;
    get_angle(&tmp.angle, &game->player->pos, &enemy->pos, enemy->dist);
    value = cast_single_ray_enemy(&tmp, 0, &type, &intersection_point);
    if (value < enemy->dist)
        return sfTrue;
    return sfFalse;
}

static void get_closer(closer_tile_t *closer, game_t *game)
{
    float tmp = 0;

    if (game->player->save->map[closer->cmp->y][closer->cmp->x] != 0)
        return;
    if (closer->next->x != SKIP && closer->next->y != SKIP
        && closer->prev.x == closer->cmp->x
        && closer->prev.y == closer->cmp->y)
        return;
    tmp = sqrt(pow((float)closer->cmp->x * TILE_SIZE + TILE_SIZE / 2 -
        game->player->pos.x, 2) + pow((float)closer->cmp->y * TILE_SIZE +
        TILE_SIZE / 2 - game->player->pos.y, 2));
    if (tmp < *closer->dist || closer->next->x == SKIP
        || closer->next->y == SKIP || (closer->prev.x == closer->next->x
        && closer->prev.y == closer->next->y)) {
        *closer->dist = tmp;
        closer->next->x = closer->cmp->x;
        closer->next->y = closer->cmp->y;
    }
}

sfBool get_next_pos(entity_t *enemy, game_t *game)
{
    sfVector2i current = {enemy->pos.x / TILE_SIZE, enemy->pos.y / TILE_SIZE};
    sfVector2i next = {SKIP, SKIP};
    float dist = 0;

    get_closer(&(closer_tile_t){&next, &(sfVector2i){current.x, current.y - 1},
        enemy->prev_tile, &dist}, game);
    get_closer(&(closer_tile_t){&next, &(sfVector2i){current.x - 1, current.y},
        enemy->prev_tile, &dist}, game);
    get_closer(&(closer_tile_t){&next, &(sfVector2i){current.x + 1, current.y},
        enemy->prev_tile, &dist}, game);
    get_closer(&(closer_tile_t){&next, &(sfVector2i){current.x, current.y + 1},
        enemy->prev_tile, &dist}, game);
    if (next.x == SKIP || next.y == SKIP)
        return sfFalse;
    enemy->next_pos.x = (float)next.x * TILE_SIZE + TILE_SIZE / 2;
    enemy->next_pos.y = (float)next.y * TILE_SIZE + TILE_SIZE / 2;
    enemy->prev_tile.x = current.x;
    enemy->prev_tile.y = current.y;
    return sfTrue;
}

void change_death_rect(
    entity_t *enemy, save_t *save, game_t *game, node_t *node)
{
    if (ENTITY[enemy->type].max_third == 0) {
        delete_node(save->entities, node, &free);
        return;
    }
    enemy->offset.y = ENTITY[enemy->type].text_size.y * 2;
    if (enemy->cooldown <= 0) {
        enemy->offset.x += ENTITY[enemy->type].text_size.x;
        enemy->cooldown = DEATH_RECT;
        if (enemy->offset.x >= ENTITY[enemy->type].max_third *
            ENTITY[enemy->type].text_size.x)
            delete_node(save->entities, node, &free);
    } else
        enemy->cooldown -= game->time_info->delta;
}

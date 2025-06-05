/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** ray_cast.c
*/

#include "save.h"
#include "game.h"
#include "entities.h"
#include <math.h>

static sfBool is_end(sfVector2f *pos, intersection_t *type, save_t *save)
{
    sfVector2i casted_pos = cast_pos(pos, type->type);

    if (casted_pos.x < 0 || casted_pos.y < 0)
        return sfFalse;
    if (casted_pos.x >= save->size.x || casted_pos.y >= save->size.y)
        return sfTrue;
    for (size_t i = 0; i < NB_WALL_TXT; ++i) {
        if (i == DOOR && get_door_pourcentage(save, &casted_pos)
            < get_pourcentage_wall(type->type, pos))
                return sfFalse;
        if (save->map[casted_pos.y][casted_pos.x] == wall_textures[i].value) {
            type->wall = i;
            return sfTrue;
        }
    }
    return sfFalse;
}

static float get_line_len(sfVector2f *point)
{
    return sqrt(point->x * point->x + point->y * point->y);
}

static void init_distances(sfVector2f *left,
    sfVector2f *top, sfVector2f *pos, sfVector2f *v)
{
    left->x = fmod(pos->x, TILE_SIZE);
    if (v->x > 0)
        left->x = TILE_SIZE - left->x;
    if (left->x == 0.0)
        left->x = TILE_SIZE;
    left->y = fabs((left->x * v->y) / v->x);
    top->y = fmod(pos->y, TILE_SIZE);
    if (v->y > 0)
        top->y = TILE_SIZE - top->y;
    if (top->y == 0.0)
        top->y = TILE_SIZE;
    top->x = fabs((top->y * v->x) / v->y);
}

static intersection_type_t move_by_left(sfVector2f *left,
    sfVector2f *pos, sfVector2f *v)
{
    if (v->x > 0)
        pos->x += left->x;
    else
        pos->x -= left->x;
    if (v->y > 0)
        pos->y += left->y;
    else
        pos->y -= left->y;
    if (v->x < 0)
        return TOP;
    return BOTTOM;
}

static intersection_type_t move_by_top(sfVector2f *top,
    sfVector2f *pos, sfVector2f *v)
{
    if (v->y > 0)
        pos->y += top->y;
    else
        pos->y -= top->y;
    if (v->x > 0)
        pos->x += top->x;
    else
        pos->x -= top->x;
    if (v->y < 0)
        return LEFT;
    return RIGHT;
}

static float jump_to_next_line(sfVector2f *pos,
    sfVector2f *v, intersection_type_t *type)
{
    sfVector2f left = {0, 0};
    sfVector2f top = {0, 0};
    float left_line_len = 0.0;
    float top_line_len = 0.0;

    init_distances(&left, &top, pos, v);
    left_line_len = get_line_len(&left);
    top_line_len = get_line_len(&top);
    if (left_line_len < top_line_len) {
        *type = move_by_left(&left, pos, v);
        return left_line_len;
    }
    *type = move_by_top(&top, pos, v);
    return top_line_len;
}

float cast_single_ray(player_t *player, float angle_offset,
    intersection_t *type, sfVector2f *intersection_point)
{
    sfVector2f pos = player->pos;
    sfVector2f v = {cos(player->angle + angle_offset),
        sin(player->angle + angle_offset)};
    float len = 0.0;

    while ((is_end(&pos, type, player->save) == sfFalse)) {
        len += jump_to_next_line(&pos, &v, &type->type);
        if (len > RENDER_DISTANCE) {
            intersection_point->x = -1;
            intersection_point->y = -1;
            return 0;
        }
    }
    *intersection_point = pos;
    return len;
}

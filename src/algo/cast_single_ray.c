/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** ray_cast.c
*/

#include "save.h"
#include "game.h"
#include <math.h>

static sfBool is_end(sfVector2f *pos, intersection_t *type, save_t *save)
{
    sfVector2i casted_pos = cast_pos(pos, type->type);

    if (casted_pos.x < 0 || casted_pos.y < 0)
        return sfFalse;
    if (casted_pos.x >= save->size.x || casted_pos.y >= save->size.x)
        return sfTrue;
    if (save->map[casted_pos.y][casted_pos.x] == 1) {
        type->wall = WALL;
        return sfTrue;
    }
    if (save->map[casted_pos.y][casted_pos.x] == 3) {
        type->wall = DESTRUCTIBLE;
        return sfTrue;
    }
    return sfFalse;
}

static float get_line_len(sfVector2f *point)
{
    return sqrt(pow(point->x, 2) + pow(point->y, 2));
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

static void save_center_ray(float angle_offset,
    player_t *player, sfVector2f *v)
{
    if (angle_offset == 0.0) {
        player->center_ray.v.x = v->x * PLAYER_SPEED;
        player->center_ray.v.y = v->y * PLAYER_SPEED;
    }
}

static void save_center_ray_success(player_t *player,
    float len, intersection_type_t type, sfVector2f *pos)
{
    player->center_ray.distance = len;
    player->center_ray.type = type;
    player->center_ray.pos = *pos;
}

float cast_single_ray(player_t *player, float angle_offset,
    intersection_t *type, sfVector2f *intersection_point)
{
    sfVector2f pos = player->pos;
    sfVector2f v = {cos(player->angle + angle_offset),
        sin(player->angle + angle_offset)};
    float len = 0.0;

    save_center_ray(angle_offset, player, &v);
    while ((is_end(&pos, type, player->save) == sfFalse)) {
        len += jump_to_next_line(&pos, &v, &type->type);
        if (len > RENDER_DISTANCE) {
            intersection_point->x = -1;
            intersection_point->y = -1;
            return 0;
        }
    }
    if (angle_offset == 0.0)
        save_center_ray_success(player, len, type->type, &pos);
    *intersection_point = pos;
    return len;
}

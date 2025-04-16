/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** ray_cast.c
*/

#include "wolf.h"
#include <math.h>

static sfBool is_end(sfVector2f *pos, which_line_t *type)
{
    sfVector2i casted_pos = {(int)(pos->x / TILE_SIZE),
        (int)(pos->y / TILE_SIZE)};

    if (*type == NONE)
        return sfFalse;
    if (*type == TOP)
        --casted_pos.x;
    if (*type == LEFT)
        --casted_pos.y;
    if (casted_pos.x < 0 || casted_pos.y < 0 ||
        casted_pos.x >= MAP_WIDTH || casted_pos.y >= MAP_WIDTH)
        return sfTrue;
    return map[casted_pos.y][casted_pos.x] != 0;
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

static which_line_t move_by_left(sfVector2f *left,
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

static which_line_t move_by_top(sfVector2f *top,
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
    sfVector2f *v, which_line_t *type)
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

float cast_single_ray(player_t *player,
    float angle_offset, which_line_t *type)
{
    sfVector2f pos = player->pos;
    sfVector2f v = {cos(player->angle + angle_offset),
        sin(player->angle + angle_offset)};
    float len = 0.0;

    *type = NONE;
    while ((is_end(&pos, type) == sfFalse)) {
        len += jump_to_next_line(&pos, &v, type);
        if (len > RENDER_DISTANCE)
            return 0;
    }
    if (angle_offset == 0.0) {
        player->v.x = v.x * PLAYER_SPEED;
        player->v.y = v.y * PLAYER_SPEED;
        player->type = *type;
    }
    return len;
}

static void add_ray_to_vertex_array(game_t *game,
    float angle_offset, which_line_t *type, float offset)
{
    float len = cast_single_ray(game->player, angle_offset, type);
    sfVertex line = {0};

    if (*type == TOP || *type == BOTTOM)
        line.color = TOP_COLOR;
    if (*type == LEFT || *type == RIGHT)
        line.color = LEFT_COLOR;
    len = (TILE_SIZE * WIN_HEIGHT) / (len * cos(angle_offset));
    line.position = (sfVector2f){offset, (WIN_HEIGHT - len) / 2};
    line.texCoords = (sfVector2f){64, 0};
    sfVertexArray_append(game->rays, line);
    if (*type == TOP || *type == BOTTOM)
        line.color = TOP_SHADOW;
    if (*type == LEFT || *type == RIGHT)
        line.color = LEFT_SHADOW;
    line.position = (sfVector2f){offset, ((WIN_HEIGHT - len) / 2) + len};
    line.texCoords = (sfVector2f){64, 128};
    sfVertexArray_append(game->rays, line);
}

void cast_all_rays(game_t *game)
{
    float offset = 0;
    float angle_offset = 0.0;
    which_line_t type = NONE;

    sfVertexArray_clear(game->rays);
    for (int i = 0; i <= NUM_RAYS; i++) {
        angle_offset = ((i / (float)NUM_RAYS) * game->player->fov) -
            (game->player->fov / 2);
        add_ray_to_vertex_array(game, angle_offset, &type, offset);
        offset += (float)NUM_RAYS / (float)WIN_WIDTH;
    }
}

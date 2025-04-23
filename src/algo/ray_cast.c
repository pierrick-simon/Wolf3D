/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** ray_cast.c
*/

#include "wolf.h"
#include <math.h>

static sfBool is_end(sfVector2f *pos, intersection_type_t *type)
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
    intersection_type_t *type, sfVector2f *intersection_point)
{
    sfVector2f pos = player->pos;
    sfVector2f v = {cos(player->angle + angle_offset),
        sin(player->angle + angle_offset)};
    float len = 0.0;

    *type = NONE;
    if (angle_offset == 0.0) {
        player->v.x = v.x * PLAYER_SPEED;
        player->v.y = v.y * PLAYER_SPEED;
    }
    while ((is_end(&pos, type) == sfFalse)) {
        len += jump_to_next_line(&pos, &v, type);
        if (len > RENDER_DISTANCE) {
            intersection_point->x = -1;
            intersection_point->y = -1;
            return 0;
        }
    }
    *intersection_point = pos;
    return len;
}

static void set_quads(sfBool start, int i, float o[2], game_t *game)
{
    sfVertex line = {.color = sfWhite};
    static float prev = 0;

    if ((start && i != 0) || i == NUM_RAYS) {
        line.position = (sfVector2f){o[0], (WIN_HEIGHT - prev) / 2};
        line.texCoords = (sfVector2f){128, 0};
        sfVertexArray_append(game->map->quads, line);
        line.position = (sfVector2f){o[0], ((WIN_HEIGHT - prev) / 2) + prev};
        line.texCoords = (sfVector2f){128, 128};
        sfVertexArray_append(game->map->quads, line);
    }
    if (start) {
        line.position = (sfVector2f){o[0], ((WIN_HEIGHT - o[1]) / 2) + o[1]};
        line.texCoords = (sfVector2f){0, 128};
        sfVertexArray_append(game->map->quads, line);
        line.position = (sfVector2f){o[0], (WIN_HEIGHT - o[1]) / 2};
        line.texCoords = (sfVector2f){0, 0};
        sfVertexArray_append(game->map->quads, line);
    }
    prev = o[1];
}

static void add_ray_to_vertex_array(game_t *game, int i, sfVector2f *prev)
{
    intersection_type_t type = NONE;
    float angle_offset = ((i / (float)NUM_RAYS) * game->player->fov) -
        (game->player->fov / 2);
    float offset = i * (float)NUM_RAYS / (float)WIN_WIDTH;
    sfVector2f pos = {0};
    float len = cast_single_ray(game->player, angle_offset, &type, &pos);
    sfBool start = (int)prev->x / TILE_SIZE != (int)pos.x / TILE_SIZE
        || (int)prev->y / TILE_SIZE != (int)pos.y / TILE_SIZE || pos.x == -1;

    len = (TILE_SIZE * WIN_HEIGHT) / (len * cos(angle_offset));
    if (game->player->is_sprinting == sfTrue)
        len /= SPRINT_COEF;
    set_quads(start, i, (float[2]){offset, len}, game);
    *prev = pos;
}

void cast_all_rays(game_t *game)
{
    sfVector2f prev = {-1, -1};

    sfVertexArray_clear(game->map->quads);
    for (int i = 0; i <= NUM_RAYS; i++) {
        add_ray_to_vertex_array(game, i, &prev);
    }
}

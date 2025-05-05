/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** cast_rays.c
*/

#include <math.h>
#include "save.h"
#include "game.h"

static void set_end_quads(game_t *game,
    float prev, float offset, wall_type_t wall)
{
    sfVertex line = {.color = sfWhite};
    static wall_type_t prev_wall = NO_WALL;
    static float prev_offset = 0;

    if (prev_offset > offset)
        prev_wall = NO_WALL;
    if (prev_wall == DESTRUCTIBLE)
        line.color = sfGreen;
    line.position = (sfVector2f){offset, (WIN_HEIGHT - prev) / 2};
    line.texCoords = (sfVector2f){128, 0};
    sfVertexArray_append(game->map->quads, line);
    line.position = (sfVector2f){offset, ((WIN_HEIGHT - prev) / 2) + prev};
    line.texCoords = (sfVector2f){128, 128};
    sfVertexArray_append(game->map->quads, line);
    prev_wall = wall;
    prev_offset = offset;
}

static void set_start_quads(game_t *game,
    float len, float offset, wall_type_t wall)
{
    sfVertex line = {.color = sfWhite};

    if (wall == DESTRUCTIBLE)
        line.color = sfGreen;
    line.position = (sfVector2f){offset, ((WIN_HEIGHT - len) / 2) + len};
    line.texCoords = (sfVector2f){0, 128};
    sfVertexArray_append(game->map->quads, line);
    line.position = (sfVector2f){offset, (WIN_HEIGHT - len) / 2};
    line.texCoords = (sfVector2f){0, 0};
    sfVertexArray_append(game->map->quads, line);
}

static void add_ray_to_vertex_array(game_t *game, int i, sfVector2f *prev)
{
    intersection_t type = {NONE, NO_WALL};
    float angle_offset = ((i / (float)NUM_RAYS) * game->player->fov) -
        (game->player->fov / 2);
    float offset = i * (float)NUM_RAYS / (float)WIN_WIDTH;
    sfVector2f pos = {0};
    float len = cast_single_ray(game->player, angle_offset, &type, &pos);
    sfBool start = (int)prev->x / TILE_SIZE != (int)pos.x / TILE_SIZE
        || (int)prev->y / TILE_SIZE != (int)pos.y / TILE_SIZE || pos.x == -1;
    static float prev_len = 0;

    len = (TILE_SIZE * WIN_HEIGHT) / (len * cos(angle_offset));
    if (game->player->is_sprinting == sfTrue)
        len /= SPRINT_COEF;
    if ((start && i != 0) || i == NUM_RAYS)
        set_end_quads(game, prev_len, offset, type.wall);
    if (start)
        set_start_quads(game, len, offset, type.wall);
    *prev = pos;
    prev_len = len;
}

void cast_all_rays(game_t *game)
{
    sfVector2f prev = {-1, -1};

    sfVertexArray_clear(game->map->quads);
    for (int i = 0; i <= NUM_RAYS; i++) {
        add_ray_to_vertex_array(game, i, &prev);
    }
}

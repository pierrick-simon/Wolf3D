/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** cast_rays.c
*/

#include <math.h>
#include "save.h"
#include "game.h"

static float get_texture_x(intersection_type_t type, sfVector2f *intersection)
{
    if (type == TOP || type == BOTTOM)
        return (fmod(intersection->y, (float)TILE_SIZE) /
            (float)TILE_SIZE) * 128.0;
    return (fmod(intersection->x, (float)TILE_SIZE) /
        (float)TILE_SIZE) * 128.0;
}

static void add_line(float offset, float len, float y, sfVertexArray *lines)
{
    sfVertex line = {.color = sfWhite};

    line.position = (sfVector2f){offset, ((WIN_HEIGHT - len) / 2) + len};
    line.texCoords = (sfVector2f){y, 128};
    sfVertexArray_append(lines, line);
    line.position = (sfVector2f){offset, (WIN_HEIGHT - len) / 2};
    line.texCoords = (sfVector2f){y, 0};
    sfVertexArray_append(lines, line);
}

static void set_line(float len, float offset,
    float y, sfVertexArray *lines)
{
    for (int i = 0; i < RAY_LENGHT; ++i)
        add_line(offset + i, len, y, lines);
}

static void add_ray_to_vertex_array(game_t *game, int i, sfVector2f *prev)
{
    intersection_t type = {NONE, WALL};
    float angle_offset = ((i / (float)NUM_RAYS) * game->player->fov) -
        (game->player->fov / 2);
    float offset = i * (float)NUM_RAYS / (float)WIN_WIDTH;
    sfVector2f pos = {0};
    float len = cast_single_ray(game->player, angle_offset, &type, &pos);

    len = (TILE_SIZE * WIN_HEIGHT) / (len * cos(angle_offset));
    if (game->player->is_sprinting == sfTrue)
        len /= SPRINT_COEF;
    set_line(len, offset, get_texture_x(type.type, &pos),
        game->map->lines[type.wall]);
    *prev = pos;
}

void cast_all_rays(game_t *game)
{
    sfVector2f prev = {-1, -1};

    for (size_t i = 0; i < NB_WALL_TXT; ++i)
        sfVertexArray_clear(game->map->lines[i]);
    for (int i = 0; i <= NUM_RAYS; i += RAY_LENGHT) {
        add_ray_to_vertex_array(game, i, &prev);
    }
}

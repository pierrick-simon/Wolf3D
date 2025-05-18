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
            (float)TILE_SIZE) * WALL_TEXTURE_X;
    return (fmod(intersection->x, (float)TILE_SIZE) /
        (float)TILE_SIZE) * WALL_TEXTURE_X;
}

static void add_line(float offset, float len,
    float pos[2], sfVertexArray *lines)
{
    sfVertex line = {.color = sfWhite};

    line.position = (sfVector2f){offset, ((WIN_HEIGHT - len) / 2) + len};
    line.texCoords = (sfVector2f){pos[Y_INDEX], pos[X_INDEX]};
    sfVertexArray_append(lines, line);
    line.position = (sfVector2f){offset, (WIN_HEIGHT - len) / 2};
    line.texCoords = (sfVector2f){pos[Y_INDEX], pos[X_INDEX] + WALL_TEXTURE_X};
    sfVertexArray_append(lines, line);
}

static void set_line(float len, float offset,
    float pos[2], sfVertexArray *lines)
{
    for (int i = 0; i < RAY_LENGTH; ++i)
        add_line(offset + i, len, pos, lines);
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
    set_line(len, offset, (float[]){wall_textures[type.wall].text_offset_y,
        get_texture_x(type.type, &pos)}, game->map->lines);
    *prev = pos;
}

void cast_all_rays(game_t *game)
{
    sfVector2f prev = {-1, -1};

    sfVertexArray_clear(game->map->lines);
    for (int i = 0; i <= NUM_RAYS; i += RAY_LENGTH) {
        add_ray_to_vertex_array(game, i, &prev);
    }
}

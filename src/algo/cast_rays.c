/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** cast_rays.c
*/

#include <math.h>
#include "save.h"
#include "game.h"

static float get_door_status(game_t *game,
    intersection_t *type, sfVector2f *pos)
{
    node_t *node = NULL;
    door_t *data = NULL;
    sfVector2i casted_pos = cast_pos(pos, type->type);

    if (type->wall != DOOR)
        return 1.0;
    node = game->player->save->doors->head;
    while (node != NULL) {
        data = (door_t *)node->data;
        if (casted_pos.x == data->pos.x &&
            casted_pos.y == data->pos.y)
            return data->state;
        node = node->next;
    }
    return 1.0;
}

static float get_texture_x(intersection_type_t type, sfVector2f *intersection)
{
    if (type == TOP || type == BOTTOM)
        return (fmod(intersection->y, (float)TILE_SIZE) /
            (float)TILE_SIZE) * WALL_TEXTURE_X;
    return (fmod(intersection->x, (float)TILE_SIZE) /
        (float)TILE_SIZE) * WALL_TEXTURE_X;
}

static void add_line(float offset, float len_factor[2],
    float pos[2], game_t *game)
{
    sfVertex line = {.color = sfWhite};

    line.position = (sfVector2f){offset, ((WIN_HEIGHT -
        len_factor[LEN_INDEX]) / 2) + (len_factor[LEN_INDEX]
        * len_factor[FACTOR_INDEX])};
    line.texCoords = (sfVector2f){pos[Y_INDEX], pos[X_INDEX]};
    sfVertexArray_append(game->map->lines, line);
    line.position = (sfVector2f){offset,
        (WIN_HEIGHT - len_factor[LEN_INDEX]) / 2};
    line.texCoords = (sfVector2f){pos[Y_INDEX], pos[X_INDEX] +
        (WALL_TEXTURE_X * len_factor[FACTOR_INDEX])};
    sfVertexArray_append(game->map->lines, line);
}

static void set_line(float offset, float len_factor[2],
    float pos[2], game_t *game)
{
    for (int i = 0; i < RAY_LENGTH; ++i)
        add_line(offset + i, len_factor, pos, game);
}

static void add_ray_to_vertex_array(game_t *game, int i, sfVector2f *prev)
{
    intersection_t type = {NONE, WALL};
    float angle_offset = ((i / (float)NUM_RAYS) * game->player->fov) -
        (game->player->fov / 2);
    float offset = i * (float)NUM_RAYS / (float)WIN_WIDTH;
    sfVector2f pos = {0};
    float len = cast_single_ray(game->player, angle_offset, &type, &pos);
    float factor = get_door_status(game, &type, &pos);

    len = (TILE_SIZE * WIN_HEIGHT) / (len * cos(angle_offset) * 1.1);
    if (game->player->is_sprinting == sfTrue)
        len /= SPRINT_COEF;
    set_line(offset, (float[]){len, factor},
        (float[]){wall_textures[type.wall].text_offset_y,
        get_texture_x(type.type, &pos)}, game);
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

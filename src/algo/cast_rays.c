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
    sfVector2i casted_pos = {0};

    if (type->wall != DOOR)
        return 1.0;
    casted_pos = cast_pos(pos, type->type);
    return get_door_pourcentage(game->player->save, &casted_pos);
}

static float get_texture_x(intersection_type_t type, sfVector2f *intersection)
{
    return get_pourcentage_wall(type, intersection) * WALL_TEXTURE_X;
}

static void add_line(float offset, float len_factor[2],
    float pos[2], game_t *game)
{
    sfVertex line = {.color = sfWhite};
    float a = ((1 - len_factor[FACTOR_INDEX]) * WALL_TEXTURE_X);

    line.position = (sfVector2f){offset * 2, ((WIN_HEIGHT -
        len_factor[LEN_INDEX]) / 2) + (len_factor[LEN_INDEX])};
    line.texCoords = (sfVector2f){pos[Y_INDEX] + a, pos[X_INDEX]};
    game->map->rays[(int)offset].down = line;
    line.position = (sfVector2f){offset * 2,
        (WIN_HEIGHT - len_factor[LEN_INDEX]) / 2};
    line.texCoords = (sfVector2f){pos[Y_INDEX] + a, pos[X_INDEX] +
        (WALL_TEXTURE_X)};
    game->map->rays[(int)offset].up = line;
}

static void set_line(int i, float len_factor[2],
    float pos[2], game_t *game)
{
    add_line(i, len_factor, pos, game);
}

static void add_ray_to_vertex_array(game_t *game, int i)
{
    intersection_t type = {NONE, WALL, NO_ENEMY};
    float angle_offset = ((i * 2 / (float)WIN_WIDTH) * game->player->fov) -
        (game->player->fov / 2);
    sfVector2f pos = {0};
    float len = cast_single_ray(game->player, angle_offset, &type, &pos);
    float factor = get_door_status(game, &type, &pos);

    len = (TILE_SIZE * WIN_HEIGHT) / (len * cos(angle_offset));
    if (game->player->is_sprinting == sfTrue)
        len /= SPRINT_COEF;
    set_line(i, (float[]){len, factor},
    (float[]){wall_textures[type.wall].text_offset_y,
        get_texture_x(type.type, &pos)}, game);
}

void cast_all_rays(game_t *game)
{
    enemies_movement(game, game->player->save->enemies);
    sort_enemies(game);
    sort_items(game);
    for (int i = 0; i < NB_RAYS; ++i)
        add_ray_to_vertex_array(game, i);
}

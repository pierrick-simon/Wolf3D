/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** center_ray.c
*/

#include "game.h"
#include <math.h>

static void is_wall(game_t *game, ray_t ray, wall_type_t type)
{
    if (type == DESTRUCTIBLE && ray.up.position.y <= (float)(WIN_HEIGHT / 2)
        && ray.down.position.y >= (float)(WIN_HEIGHT / 2))
        game->map->is_wall = sfTrue;
    else
        game->map->is_wall = sfFalse;
}

void center_ray(game_t *game)
{
    player_t *player = game->player;
    intersection_t type = {NONE, WALL};
    sfVector2f pos = {0};

    player->center_ray.distance = cast_single_ray(player, 0, &type, &pos);
    is_wall(game, game->map->rays[(int)(((float)NB_RAYS / 2.0))], type.wall);
    player->center_ray.pos = pos;
    player->center_ray.type = type.type;
    player->v = (sfVector2f){cos(player->angle),
        sin(player->angle)};
    player->n = (sfVector2f){(player->v.y * (DEG(FOV) / 100.0)),
        (-player->v.x * (DEG(FOV) / 100.0))};
}

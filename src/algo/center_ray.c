/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** center_ray.c
*/

#include "game.h"
#include <math.h>

void center_ray(player_t *player)
{
    intersection_t type = {NONE, WALL};
    sfVector2f pos = {0};

    player->center_ray.distance = cast_single_ray(player, 0, &type, &pos);
    player->center_ray.pos = pos;
    player->center_ray.type = type.type;
    player->v = (sfVector2f){cos(player->angle),
        sin(player->angle)};
    player->n = (sfVector2f){(player->v.y * (DEG(FOV) / 100.0)),
        (-player->v.x * (DEG(FOV) / 100.0))};
}

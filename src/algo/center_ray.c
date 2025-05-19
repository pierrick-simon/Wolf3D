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
    player->center_ray.v = (sfVector2f){cos(player->angle) * 100,
        sin(player->angle) * 100};
}

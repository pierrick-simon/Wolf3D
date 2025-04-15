/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init_player.c
*/

#include "wolf.h"

void init_player(player_t *player)
{
    player->angle = 0;
    player->x = MAP_WIDTH / (TILE_SIZE * 2);
    player->y = MAP_HEIGHT / (TILE_SIZE * 2);
}
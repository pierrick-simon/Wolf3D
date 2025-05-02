/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** cast_pos.c
*/

#include "game.h"

sfVector2i cast_pos(sfVector2f *pos, intersection_type_t type)
{
    sfVector2i casted_pos = {(int)(pos->x / TILE_SIZE),
        (int)(pos->y / TILE_SIZE)};

    if (type == NONE)
        return (sfVector2i){-1, -1};
    if (type == TOP)
        --casted_pos.x;
    if (type == LEFT)
        --casted_pos.y;
    return casted_pos;
}

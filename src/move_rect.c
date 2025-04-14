/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_rect
*/

#include "wolf.h"

void move_rect(sprite_t *sprite, int offset, int nb_tile)
{
    sprite->rectangle.left += offset;
    if (sprite->rectangle.left >= offset * nb_tile)
        sprite->rectangle.left = 0;
    sfSprite_setTextureRect(sprite->sprite, sprite->rectangle);
}
/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_rect
*/

#include "wolf.h"

void move_rect(sfSprite *sprite, sfIntRect *rect, int offset, int nb_tile)
{
    (*rect).left += offset;
    if ((*rect).left >= offset * nb_tile)
        (*rect).left = 0;
    sfSprite_setTextureRect(sprite, *rect);
}

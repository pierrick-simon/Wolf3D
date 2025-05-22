/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** get_color.c
*/

#include "game.h"

sfColor get_color(float len)
{
    float a = 0;

    if (len < START_BLACK)
        a = 0;
    else if (len > END_BLACK)
        a = 1;
    else
        a = (len - START_BLACK) / (END_BLACK - START_BLACK);
    a = 1 - a;
    return sfColor_fromRGB(a * MAX_COLOR, a * MAX_COLOR, a * MAX_COLOR);
}

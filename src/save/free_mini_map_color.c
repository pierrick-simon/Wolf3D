/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** free_mini_map_color
*/

#include <stdlib.h>
#include "save.h"

void free_mini_map_color(sfColor **color, int y)
{
    for (int i = 0; i < y; i++)
        free(color[i]);
    free(color);
}

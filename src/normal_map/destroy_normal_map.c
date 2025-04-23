/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_normal_map
*/

#include "wolf.h"
#include <stdlib.h>

void destroy_normal_map(void *structure)
{
    normal_map_t *normal_map = (normal_map_t *)structure;

    if (normal_map->draw != NULL)
        free_draw_textbox(normal_map->draw, -1);
    free(normal_map);
}

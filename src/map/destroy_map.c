/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_map
*/

#include "save.h"
#include <stdlib.h>

void destroy_map(void *structure)
{
    select_map_t *map = (select_map_t *)structure;

    if (map->draw != NULL)
        free_draw_textbox(map->draw, -1);
    free(map);
}

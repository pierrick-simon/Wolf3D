/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_edit_map
*/

#include "editor.h"
#include <stdlib.h>

void destroy_edit_map(void *structure)
{
    edit_map_t *edit_map = (edit_map_t *)structure;

    if (edit_map->draw != NULL)
        free_draw_textbox(edit_map->draw, -1);
    if (edit_map->shape != NULL)
        sfConvexShape_destroy(edit_map->shape);
    free(edit_map);
}

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
    if (edit_map->draw_map != NULL) {
        if (edit_map->draw_map->shape != NULL)
            sfConvexShape_destroy(edit_map->draw_map->shape);
        free(edit_map->draw_map);
    }
    if (edit_map->buttons != NULL) {
        if (edit_map->buttons->rectangle != NULL)
            sfRectangleShape_destroy(edit_map->buttons->rectangle);
        free(edit_map->buttons);
    }
    free(edit_map);
}

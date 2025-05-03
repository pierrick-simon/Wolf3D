/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_maps
*/

#include "save.h"
#include "linked_list.h"
#include <stdlib.h>

void destroy_maps(void *structure)
{
    maps_t *maps = (maps_t *)structure;

    if (maps->draw != NULL)
        free_draw_textbox(maps->draw, -1);
    if (maps->info != NULL) {
        if (maps->info->list != NULL)
            free_linked_list(maps->info->list, &free_node_file);
        free(maps->info);
    }
    free(maps);
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_normal_map
*/

#include "save.h"
#include "linked_list.h"
#include <stdlib.h>

void destroy_normal_map(void *structure)
{
    normal_map_t *normal_map = (normal_map_t *)structure;

    if (normal_map->draw != NULL)
        free_draw_textbox(normal_map->draw, -1);
    if (normal_map->info != NULL) {
        if (normal_map->info->list != NULL)
            free_linked_list(normal_map->info->list, &free_node_file);
        free(normal_map->info);
    }
    free(normal_map);
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_your_maps
*/

#include "save.h"
#include "linked_list.h"
#include <stdlib.h>

void destroy_your_maps(void *structure)
{
    levels_t *your_maps = (levels_t *)structure;

    if (your_maps->draw != NULL)
        free_draw_textbox(your_maps->draw, -1);
    if (your_maps->info != NULL) {
        if (your_maps->info->list != NULL)
            free_linked_list(your_maps->info->list, &free_node_file);
        free(your_maps->info);
    }
    free(your_maps);
}

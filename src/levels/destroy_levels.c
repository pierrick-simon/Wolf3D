/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_levels
*/

#include "save.h"
#include "linked_list.h"
#include <stdlib.h>

void destroy_levels(void *structure)
{
    levels_t *levels = (levels_t *)structure;

    if (levels->draw != NULL)
        free_draw_textbox(levels->draw, -1);
    if (levels->info != NULL) {
        if (levels->info->list != NULL)
            free_linked_list(levels->info->list, &free_node_file);
        free(levels->info);
    }
    free(levels);
}

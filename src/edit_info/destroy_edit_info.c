/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_edit_info
*/

#include "editor.h"
#include <stdlib.h>

void destroy_edit_info(void *structure)
{
    edit_info_t *edit_info = (edit_info_t *)structure;

    if (edit_info->draw != NULL)
        free_draw_textbox(edit_info->draw, -1);
    free(edit_info);
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_leave
*/

#include "quit.h"
#include <stdlib.h>

void destroy_leave(void *structure)
{
    leave_t *leave = (leave_t *)structure;

    if (leave->draw != NULL)
        free_draw_textbox(leave->draw, -1);
    free(leave);
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_pause
*/

#include "wolf.h"
#include <stdlib.h>

void destroy_pause(void *structure)
{
    pause_t *pause = (pause_t *)structure;

    if (pause->draw != NULL)
        free_draw_textbox(pause->draw, -1);
    free(pause);
}

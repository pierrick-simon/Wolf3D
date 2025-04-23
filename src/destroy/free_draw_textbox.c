/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** free_draw_textbox
*/

#include "wolf.h"
#include <stdlib.h>

void free_draw_textbox(draw_textbox_t *draw, int stop)
{
    int i = 0;

    while (draw[i].str != NULL && (i < stop || stop == -1)) {
        free(draw[i].str);
        i++;
    }
    free(draw);
}

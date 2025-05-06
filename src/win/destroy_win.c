/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_win
*/

#include "quit.h"
#include <stdlib.h>

void destroy_win(void *structure)
{
    win_t *win = (win_t *)structure;

    if (win->draw != NULL)
        free_draw_textbox(win->draw, -1);
    if (win->clock != NULL)
        sfClock_destroy(win->clock);
    if (win->danse != NULL) {
        if (win->danse->texture != NULL)
            sfTexture_destroy(win->danse->texture);
        if (win->danse->sprite != NULL)
            sfSprite_destroy(win->danse->sprite);
        free(win->danse);
    }
    if (win->name != NULL)
        free(win->name);
    free(win);
}

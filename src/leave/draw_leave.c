/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_leave
*/

#include "quit.h"

void draw_leave(system_t *sys, void *structure)
{
    leave_t *leave = (leave_t *)structure;

    leave_events(sys, leave);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_LEAVE; i++)
        draw_string(sys, sys->textbox, &leave->draw[i]);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

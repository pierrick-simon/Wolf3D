/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_pause
*/

#include "wolf.h"

void draw_pause(system_t *sys, void *structure)
{
    pause_t *pause = (pause_t *)structure;

    pause_events(sys, pause);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_PAUSE; i++)
        draw_string(sys, sys->textbox, &pause->draw[i]);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

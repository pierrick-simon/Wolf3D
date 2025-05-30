/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_choose
*/

#include "game_menu.h"
#include "save.h"
#include "my.h"
#include <stdio.h>

void draw_choose(system_t *sys, void *structure)
{
    choose_t *choose = (choose_t *)structure;

    choose_events(sys, choose);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_CHOOSE; i++)
        draw_string(sys, sys->textbox, &choose->draw[i]);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

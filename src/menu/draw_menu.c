/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_menu
*/

#include "wolf.h"

void draw_menu(system_t *sys, void *structure)
{
    menu_t *menu = (menu_t *)structure;

    menu_events(sys, menu);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_MENU; i++)
        draw_string(sys, sys->textbox, &menu->draw[i]);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_menu
*/

#include "wolf.h"

void draw_background(system_t *sys, background_t *background)
{
    sfRenderWindow_drawSprite(sys->window, background->wallpaper_s, NULL);
    sfRenderWindow_drawSprite(sys->window, background->guy_s, NULL);
}

void draw_menu(system_t *sys, void *structure)
{
    menu_t *menu = (menu_t *)structure;

    menu_events(sys, menu);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_normal_map
*/

#include "wolf.h"

void draw_normal_map(system_t *sys, void *structure)
{
    normal_map_t *normal_map = (normal_map_t *)structure;

    normal_map_events(sys, normal_map);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_MENU; i++)
        draw_string(sys, sys->textbox, &normal_map->draw[i]);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

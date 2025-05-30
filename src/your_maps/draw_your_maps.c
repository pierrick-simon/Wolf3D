/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_your_maps
*/

#include "save.h"
#include "linked_list.h"

void draw_your_maps(system_t *sys, void *structure)
{
    levels_t *your_maps = (levels_t *)structure;

    your_maps_events(sys, your_maps);
    update_list(your_maps->info, "your_maps");
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    draw_string(sys, sys->textbox, &your_maps->draw[LEVELS_TITLE]);
    draw_string(sys, sys->textbox, &your_maps->draw[LEVELS_SUB]);
    draw_string(sys, sys->textbox, &your_maps->draw[LEVELS_BACK]);
    draw_save(sys, your_maps->info, your_maps->draw, LEVELS_SAVE1);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

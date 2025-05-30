/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_maps
*/

#include "save.h"
#include "linked_list.h"

void draw_maps(system_t *sys, void *structure)
{
    maps_t *maps = (maps_t *)structure;

    maps_events(sys, maps);
    update_list(maps->info, "maps");
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    draw_string(sys, sys->textbox, &maps->draw[LEVELS_TITLE]);
    draw_string(sys, sys->textbox, &maps->draw[LEVELS_SUB]);
    draw_string(sys, sys->textbox, &maps->draw[LEVELS_BACK]);
    draw_save(sys, maps->info, maps->draw, LEVELS_SAVE1);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

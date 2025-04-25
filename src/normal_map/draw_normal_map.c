/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_normal_map
*/

#include "save.h"
#include "linked_list.h"

void draw_normal_map(system_t *sys, void *structure)
{
    normal_map_t *normal_map = (normal_map_t *)structure;

    normal_map_events(sys, normal_map);
    update_list(normal_map->info, "normal_map");
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    draw_string(sys, sys->textbox, &normal_map->draw[NOR_MAP_TITLE]);
    draw_string(sys, sys->textbox, &normal_map->draw[NOR_MAP_SUB]);
    draw_string(sys, sys->textbox, &normal_map->draw[NOR_MAP_BACK]);
    draw_save(sys, normal_map->info, normal_map->draw, NOR_MAP_SAVE1);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_levels
*/

#include "save.h"
#include "linked_list.h"

void draw_levels(system_t *sys, void *structure)
{
    levels_t *levels = (levels_t *)structure;

    sys->dir = "levels";
    levels_events(sys, levels);
    update_list(levels->info, "levels");
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    draw_string(sys, sys->textbox, &levels->draw[LEVELS_TITLE]);
    draw_string(sys, sys->textbox, &levels->draw[LEVELS_SUB]);
    draw_string(sys, sys->textbox, &levels->draw[LEVELS_BACK]);
    draw_save(sys, levels->info, levels->draw, LEVELS_SAVE1);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

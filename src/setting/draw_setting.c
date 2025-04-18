/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_setting
*/

#include "wolf.h"

void draw_setting(system_t *sys, void *structure)
{
    setting_t *setting = (setting_t *)structure;

    setting_events(sys, setting);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_SETTING; i++) {
        if (setting->str == i)
            draw_string(sys, sys->textbox, &str_setting[i], sfRed);
        else
            draw_string(sys, sys->textbox, &str_setting[i], sfWhite);
    }
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}

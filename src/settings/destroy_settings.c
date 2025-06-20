/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_setting
*/

#include "game_menu.h"
#include <stdlib.h>

void destroy_settings(void *structure)
{
    setting_t *setting = (setting_t *)structure;

    if (setting->draw != NULL)
        free_draw_textbox(setting->draw, -1);
    if (setting->rect != NULL)
        sfRectangleShape_destroy(setting->rect);
    free(setting);
}

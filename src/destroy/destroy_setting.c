/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_setting
*/

#include "wolf.h"
#include <stdlib.h>

void destroy_setting(void *structure)
{
    setting_t *setting = (setting_t *)structure;

    if (setting->draw != NULL)
        free_draw_textbox(setting->draw, -1);
    free(setting);
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_setting
*/

#include "wolf.h"
#include <stdlib.h>

void *init_settings(void)
{
    setting_t *setting = malloc(sizeof(setting_t));

    if (setting == NULL)
        return NULL;
    setting->str = SETTING_FULL;
    setting->draw = init_from_conf("config_file/setting.conf");
    setting->rect = sfRectangleShape_create();
    if (setting->draw == NULL || setting->rect == NULL)
        return NULL;
    sfRectangleShape_setOutlineThickness(setting->rect, 2);
    sfRectangleShape_setOutlineColor(setting->rect, sfWhite);
    return (void *)setting;
}

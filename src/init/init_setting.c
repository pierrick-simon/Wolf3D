/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_setting
*/

#include "wolf.h"
#include <stdlib.h>

void *init_setting(void)
{
    setting_t *setting = malloc(sizeof(setting_t));

    if (setting == NULL)
        return NULL;
    setting->str = SETTING_FULL;
    setting->draw = init_from_conf("config_file/setting.conf");
    if (setting->draw == NULL)
        return NULL;
    return (void *)setting;
}

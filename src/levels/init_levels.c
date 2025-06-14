/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_levels
*/

#include "save.h"
#include "game_menu.h"
#include <stdlib.h>

static void init_info_save(info_save_t *info)
{
    info->file = 0;
    info->list = NULL;
    info->current_file = NULL;
    info->update = sfFalse;
    info->nb_page = 0;
}

void *init_levels(void)
{
    levels_t *levels = malloc(sizeof(levels_t));

    if (levels == NULL)
        return NULL;
    levels->str = MENU_PLAY;
    levels->draw = init_from_conf(str_conf[CONF_LEVELS]);
    if (levels->draw == NULL)
        return NULL;
    levels->info = malloc(sizeof(info_save_t));
    if (levels->info == NULL)
        return NULL;
    init_info_save(levels->info);
    return (void *)levels;
}

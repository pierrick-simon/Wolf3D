/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_maps
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

void *init_maps(void)
{
    maps_t *maps = malloc(sizeof(maps_t));

    if (maps == NULL)
        return NULL;
    maps->str = MENU_PLAY;
    maps->draw = init_from_conf(str_conf[CONF_MAPS]);
    if (maps->draw == NULL)
        return NULL;
    maps->info = malloc(sizeof(info_save_t));
    if (maps->info == NULL)
        return NULL;
    init_info_save(maps->info);
    return (void *)maps;
}

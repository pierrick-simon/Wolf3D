/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_normal_map
*/

#include "save.h"
#include <stdlib.h>

static void init_info_save(info_save_t *info)
{
    info->file = 0;
    info->list = NULL;
    info->current_file = NULL;
    info->update = sfFalse;
    info->nb_page = 0;
}

void *init_normal_map(void)
{
    normal_map_t *normal_map = malloc(sizeof(normal_map_t));

    if (normal_map == NULL)
        return NULL;
    normal_map->str = MENU_PLAY;
    normal_map->draw = init_from_conf("config_file/normal_map.conf");
    if (normal_map->draw == NULL)
        return NULL;
    normal_map->info = malloc(sizeof(info_save_t));
    if (normal_map->info == NULL)
        return NULL;
    init_info_save(normal_map->info);
    return (void *)normal_map;
}

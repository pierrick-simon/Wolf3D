/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_map
*/

#include "save.h"
#include <stdlib.h>

void *init_map(void)
{
    select_map_t *map = malloc(sizeof(select_map_t));

    if (map == NULL)
        return NULL;
    map->str = MAP_PLAY;
    map->save = sfFalse;
    map->check = sfFalse;
    map->draw = init_from_conf("config_file/map.conf");
    if (map->draw == NULL)
        return NULL;
    return (void *)map;
}

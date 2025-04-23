/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_normal_map
*/

#include "wolf.h"
#include <stdlib.h>

void *init_normal_map(void)
{
    normal_map_t *normal_map = malloc(sizeof(normal_map_t));

    if (normal_map == NULL)
        return NULL;
    normal_map->str = MENU_PLAY;
    normal_map->draw = init_from_conf("config_file/normal_map.conf");
    if (normal_map->draw == NULL)
        return NULL;
    return (void *)normal_map;
}

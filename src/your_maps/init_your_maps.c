/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_your_maps
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

void *init_your_maps(void)
{
    levels_t *your_maps = malloc(sizeof(levels_t));

    if (your_maps == NULL)
        return NULL;
    your_maps->str = MENU_PLAY;
    your_maps->draw = init_from_conf(str_conf[CONF_LEVELS]);
    if (your_maps->draw == NULL)
        return NULL;
    your_maps->info = malloc(sizeof(info_save_t));
    if (your_maps->info == NULL)
        return NULL;
    init_info_save(your_maps->info);
    return (void *)your_maps;
}

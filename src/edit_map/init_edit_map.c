/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_edit_map
*/

#include "editor.h"
#include <stdlib.h>
#include <stdio.h>

void *init_edit_map(void)
{
    edit_map_t *edit_map = malloc(sizeof(edit_map_t));

    if (edit_map == NULL)
        return NULL;
    edit_map->str = EDIT_MAP_SAVE;
    edit_map->draw = init_from_conf(str_conf[CONF_EDIT_MAP]);
    edit_map->shape = sfConvexShape_create();
    if (edit_map->draw == NULL || edit_map->shape == NULL)
        return NULL;
    for (int i = 0; i < NB_EDIT_MAP; i++)
        edit_map->draw[i].color = sfBlack;
    edit_map->update = sfFalse;
    sfConvexShape_setOutlineColor(edit_map->shape, sfBlack);
    sfConvexShape_setOutlineThickness(edit_map->shape, 1);
    return (void *)edit_map;
}

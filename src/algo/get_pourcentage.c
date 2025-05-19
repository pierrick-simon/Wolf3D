/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** get_pourcentage.c
*/

#include "game.h"
#include "save.h"
#include <math.h>

float get_pourcentage_wall(intersection_type_t type, sfVector2f *intersection)
{
    if (type == TOP || type == BOTTOM)
        return (fmod(intersection->y, (float)TILE_SIZE) /
            (float)TILE_SIZE);
    return (fmod(intersection->x, (float)TILE_SIZE) /
        (float)TILE_SIZE);
}

float get_door_pourcentage(save_t *save, sfVector2i *pos)
{
    node_t *node = NULL;
    door_t *data = NULL;

    node = save->doors->head;
    while (node != NULL) {
        data = (door_t *)node->data;
        if (pos->x == data->pos.x &&
            pos->y == data->pos.y)
            return data->state;
        node = node->next;
    }
    return 1.0;
}

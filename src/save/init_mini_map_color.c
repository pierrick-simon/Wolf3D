/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_mini_map_color
*/

#include "save.h"
#include "game.h"
#include "stdlib.h"

int init_mini_map_color(save_t *save)
{
    int x = save->size.x + MINI_MAP_OFFSET * 2;
    int y = save->size.y + MINI_MAP_OFFSET * 2;

    save->mini_map = malloc(sizeof(sfColor *) * y);
    if (save->mini_map == NULL)
        return ERROR;
    for (int i = 0; i < y; i++) {
        save->mini_map[i] = malloc(sizeof(sfColor *) * x);
        if (save->mini_map[i] == NULL) {
            free_mini_map_color(save->mini_map, i - 1);
            return ERROR;
        }
        for (int j = 0; j < x; j++)
            save->mini_map[i][j] = sfBlack;
    }
    return SUCCESS;
}

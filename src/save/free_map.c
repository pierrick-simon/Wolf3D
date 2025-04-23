/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_save
*/

#include "save.h"
#include <stdlib.h>

void free_map(int size, int **map)
{
    for (int i = 0; i < size; i++)
        free(map[i]);
    free(map);
}

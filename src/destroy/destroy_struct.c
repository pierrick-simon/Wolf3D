/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_struct
*/

#include "wolf.h"
#include "scene.h"
#include <stdlib.h>

void destroy_struct(void **structure, int stop)
{
    for (int i = 0; i < stop; i++) {
        if (structure[i] != NULL)
            SCENE[i].destroy(structure[i]);
    }
    free(structure);
}

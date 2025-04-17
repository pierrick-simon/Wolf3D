/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_struct
*/

#include "wolf.h"
#include "scene.h"
#include <stdlib.h>

void **init_struct(void)
{
    void **structure = malloc(sizeof(void *) * NB_SCENE);

    if (structure == NULL)
        return NULL;
    for (int i = 0; i < NB_SCENE; i++) {
        structure[i] = SCENE[i].init();
        if (structure[i] == NULL) {
            destroy_struct(structure, i);
            return NULL;
        }
    }
    return structure;
}

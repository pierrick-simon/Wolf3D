/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_struct
*/

#include "load_screen.h"
#include "scene.h"
#include <stdlib.h>

void **init_struct(load_screen_t *start)
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
        draw_load_screen(start, i);
    }
    return structure;
}

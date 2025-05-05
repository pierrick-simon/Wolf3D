/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** sys_loop
*/

#include "wolf.h"
#include "scene.h"

static void find_scene(system_t *sys, void **structure)
{
    for (int i = 0; i < NB_SCENE; i++) {
        if ((int)sys->state->scene == SCENE[i].id) {
            SCENE[i].draw(sys, structure[i]);
            break;
        }
    }
}

void sys_loop(system_t *sys, void **structure)
{
    while (sfRenderWindow_isOpen(sys->window) == sfTrue) {
        find_scene(sys, structure);
    }
}

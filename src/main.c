/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** main
*/

#include "wolf.h"

int main(void)
{
    system_t sys = {NULL};
    void **structure = init_struct();

    if (structure == NULL || init_system(&sys) == EXIT_F) {
        destroy_sys(&sys);
        return EXIT_F;
    }
    sys_loop(&sys, structure);
    destroy_struct(structure, NB_SCENE);
    destroy_sys(&sys);
    return EXIT_S;
}

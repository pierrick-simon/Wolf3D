/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** main
*/

#include "load_screen.h"

int main(__maybe_unused int ac, __maybe_unused char **av, char **env)
{
    system_t sys = {NULL};
    void **structure = NULL;

    if (check_env(env) == ERROR)
        return ERROR;
    if (load_screen(&structure, &sys) == ERROR)
        return ERROR;
    sys_loop(&sys, structure);
    destroy_struct(structure, NB_SCENE);
    destroy_sys(&sys);
    return SUCCESS;
}

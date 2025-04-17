/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_sys
*/

#include "wolf.h"

void destroy_sys(system_t *sys)
{
    if (sys->music != NULL)
        sfMusic_destroy(sys->music);
    if (sys->clock != NULL)
        sfClock_destroy(sys->clock);
    if (sys->window != NULL)
        sfRenderWindow_destroy(sys->window);
}

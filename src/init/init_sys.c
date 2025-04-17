/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_sys
*/

#include "wolf.h"

int init_system(system_t *sys)
{
    sys->window = create_window(sfTitlebar | sfClose, 0.9);
    sys->clock = sfClock_create();
    sys->music = sfMusic_createFromFile("asset/music.ogg");
    if (sys->window == NULL || sys->clock == NULL || sys->music == NULL)
        return EXIT_F;
    sys->fullscreen = sfFalse;
    return EXIT_S;
}

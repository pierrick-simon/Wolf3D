/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_sys
*/

#include "wolf.h"

int init_system(system_t *sys)
{
    sys->window = create_window(sfFullscreen, 1);
    sys->clock = sfClock_create();
    sys->music = sfMusic_createFromFile("asset/music.ogg");
    if (sys->window == NULL || sys->clock == NULL || sys->music == NULL)
        return EXIT_F;
    sys->fullscreen = sfTrue;
    sys->scene = GAME;
    return EXIT_S;
}

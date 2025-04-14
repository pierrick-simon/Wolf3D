/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** creat_window
*/

#include "wolf.h"

sfRenderWindow *create_window(void)
{
    sfRenderWindow *window = {0};
    sfVideoMode size_of_window = {0};

    size_of_window.height = WIN_HEIGHT;
    size_of_window.width = WIN_WIDTH;
    size_of_window.bitsPerPixel = WIN_BITS;
    window = sfRenderWindow_create(size_of_window,
        WIN_NAME, sfNone, NULL);
    if (window == NULL)
        return NULL;
    sfRenderWindow_setFramerateLimit(window, WIN_FRAME);
    return window;
}

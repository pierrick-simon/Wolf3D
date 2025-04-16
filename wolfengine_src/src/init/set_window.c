/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** set_window.c
*/

#include "wolfengine.h"

sfRenderWindow *set_window(void)
{
    sfRenderWindow *window = {0};
    sfVideoMode videomode = {0};

    videomode.height = WIN_HEIGHT;
    videomode.width = WIN_WIDTH;
    videomode.bitsPerPixel = WIN_BITS;
    window = sfRenderWindow_create(
        videomode, WIN_TITLE, sfNone, NULL);
    if (window == NULL)
        return NULL;
    sfRenderWindow_setFramerateLimit(window, WIN_FRAME);
    return window;
}

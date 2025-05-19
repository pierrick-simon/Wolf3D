/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** create_window
*/

#include "wolf.h"

sfRenderWindow *create_window(sfUint32 style, double coef)
{
    sfRenderWindow *window = {0};
    sfVideoMode size_of_window = {0};

    size_of_window.height = WIN_HEIGHT;
    size_of_window.width = WIN_WIDTH;
    size_of_window.bitsPerPixel = WIN_BITS;
    window = sfRenderWindow_create(size_of_window,
        WINDOW_NAME, style, NULL);
    if (window == NULL)
        return NULL;
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfRenderWindow_setFramerateLimit(window, WIN_FRAME);
    sfRenderWindow_setSize(
        window, (sfVector2u){WIN_WIDTH * coef, WIN_HEIGHT *coef});
    return window;
}

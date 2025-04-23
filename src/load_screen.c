/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** load_screen
*/

#include "load_screen.h"
#include <unistd.h>

static void destroy_load_screen(load_screen_t *start)
{
    if (start->rect != NULL)
        sfRectangleShape_destroy(start->rect);
    if (start->window != NULL)
        sfRenderWindow_destroy(start->window);
}

static int init_load_screen(load_screen_t *start)
{
    sfVector2f pos = (sfVector2f){RECT_OFFSET, WIN_HEIGHT * 0.8};

    start->window = create_window(sfTitlebar, 0.5);
    start->rect = sfRectangleShape_create();
    if (start->rect == NULL || start->window == NULL) {
        destroy_load_screen(start);
        return ERROR;
    }
    start->nb_init = 0;
    sfRectangleShape_setOutlineColor(start->rect, sfWhite);
    sfRectangleShape_setOutlineThickness(start->rect, 2);
    sfRectangleShape_setPosition(start->rect, pos);
    return SUCCESS;
}

void draw_load_screen(load_screen_t *start, double ind)
{
    double total_x = WIN_WIDTH - RECT_OFFSET * 2;
    double current_x = total_x * ind / NB_SCENE;

    sfRenderWindow_clear(start->window, sfBlack);
    sfRectangleShape_setFillColor(start->rect, sfTransparent);
    sfRectangleShape_setSize(start->rect, (sfVector2f){total_x, RECT_OFFSET});
    sfRenderWindow_drawRectangleShape(start->window, start->rect, NULL);
    sfRectangleShape_setFillColor(start->rect, sfWhite);
    sfRectangleShape_setSize(start->rect,
        (sfVector2f){current_x, RECT_OFFSET});
    sfRenderWindow_drawRectangleShape(start->window, start->rect, NULL);
    sfRenderWindow_display(start->window);
}

int load_screen(void ***structure, system_t *sys)
{
    load_screen_t start = {NULL};

    if (init_load_screen(&start) == ERROR)
        return ERROR;
    *structure = init_struct(&start);
    if (*structure == NULL || init_system(sys, &start) == ERROR) {
        destroy_sys(sys);
        destroy_load_screen(&start);
        return ERROR;
    }
    destroy_load_screen(&start);
    return SUCCESS;
}

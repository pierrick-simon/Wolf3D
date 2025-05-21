/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_menu
*/

#include "game_menu.h"
#include <stdlib.h>

void destroy_menu(void *structure)
{
    menu_t *menu = (menu_t *)structure;

    if (menu->draw != NULL)
        free_draw_textbox(menu->draw, -1);
    free(menu);
}

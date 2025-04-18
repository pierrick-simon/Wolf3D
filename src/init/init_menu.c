/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_menu
*/

#include "wolf.h"
#include <stdlib.h>

void *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (menu == NULL)
        return NULL;
    menu->str = MENU_PLAY;
    return (void *)menu;
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_menu
*/

#include "wolf.h"
#include <stdlib.h>

void destroy_menu(void *structure)
{
    menu_t *menu = (menu_t *)structure;

    free(menu);
}

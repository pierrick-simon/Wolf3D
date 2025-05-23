/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_menu
*/

#include "game_menu.h"
#include <stdlib.h>

void *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (menu == NULL)
        return NULL;
    menu->str = MENU_PLAY;
    menu->draw = init_from_conf(str_conf[CONF_MENU]);
    if (menu->draw == NULL)
        return NULL;
    return (void *)menu;
}

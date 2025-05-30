/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_choose
*/

#include "game_menu.h"
#include <stdlib.h>

void destroy_choose(void *structure)
{
    choose_t *choose = (choose_t *)structure;

    if (choose->draw != NULL)
        free_draw_textbox(choose->draw, -1);
    free(choose);
}

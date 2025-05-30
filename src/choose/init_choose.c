/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_choose
*/

#include "game_menu.h"
#include <stdlib.h>

void *init_choose(void)
{
    choose_t *choose = malloc(sizeof(choose_t));

    if (choose == NULL)
        return NULL;
    choose->str = CHOOSE_LEVELS;
    choose->draw = init_from_conf(str_conf[CONF_CHOOSE]);
    if (choose->draw == NULL)
        return NULL;
    return (void *)choose;
}

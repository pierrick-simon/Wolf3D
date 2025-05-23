/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_pause
*/

#include "game_menu.h"
#include <stdlib.h>

void *init_pause(void)
{
    pause_t *pause = malloc(sizeof(pause_t));

    if (pause == NULL)
        return NULL;
    pause->str = PAUSE_RESUME;
    pause->draw = init_from_conf(str_conf[CONF_PAUSE]);
    if (pause->draw == NULL)
        return NULL;
    return (void *)pause;
}

/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_leave
*/

#include "quit.h"
#include <stdlib.h>

void *init_leave(void)
{
    leave_t *leave = malloc(sizeof(leave_t));

    if (leave == NULL)
        return NULL;
    leave->str = LEAVE_SAVE;
    leave->draw = init_from_conf(str_conf[CONF_LEAVE]);
    if (leave->draw == NULL)
        return NULL;
    return (void *)leave;
}

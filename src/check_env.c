/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** check_env
*/

#include "wolf.h"
#include <string.h>

int check_env(char **env)
{
    int i = 0;

    while (env[i] != 0) {
        if (strstr(env[i], "DISPLAY=:") != NULL)
            return SUCCESS;
        i++;
    }
    return ERROR;
}
